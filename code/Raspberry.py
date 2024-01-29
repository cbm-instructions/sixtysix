import serial

import numpy as np
import random
from PIL import Image
from urllib.request import urlretrieve
import sqlite3
import datetime
import io

import pygame
pygame.init() 
pygame.mixer.init()

import logging
import threading
import time
from pynput import keyboard
from pynput import mouse

# ports are variable and must be adjusted for each device
arduino = serial.Serial(port='/dev/ttyACM0', baudrate=9600, timeout=.1)
qr_scanner = serial.Serial(port='/dev/ttyAMA0', baudrate= 9600, timeout=1)

qr_scanner.reset_input_buffer()
qr_data = []
qr_codes = []
image = None
session_uid = ""
opened = False

# path of the folder, which contains the mp3 files
sound_path = '/home/cbm66/Desktop/Sounds/'
#names of all mp3 files
file_path_sound_array = ['willst_teile.mp3', 'gutes_zeug.mp3', 'letzte_chance.mp3', 'fluestern_brauchst_teile.mp3']

class SoundThread(threading.Thread):
	"""
 	Used to play the mp3 files, when someone triggers the ultra sound meter.
 	"""
	def __init__ (self, file_path):
		super().__init__()
		self.file_path=file_path
		self.is_playing = False
		self.daemon = True

	"""
 	Used to play a mp3 (given by path).
  	Stops for 60 sec after playing the sound.
   	'self.is_playing' is a global flag to prevent multiple threads from running simultaneously.
 	"""
	def run(self):
		pygame.mixer.music.load(self.file_path)
		pygame.mixer.music.play()
		
		self.is_playing = True
		while pygame.mixer.music.get_busy():
			continue
		
		time.sleep(60)
		self.is_playing = False	
		
sound_Thread = None	

def take_picture():
	"""
 	Used to take pictures and save them in the given path.
  	Adjust the IP-adress in urlretrieve() to the ip-adress of the camera in your network
 	"""
	filename = str(datetime.datetime.now().timestamp()) + "_pic"
	path = '/home/cbm66/Desktop/pics/' + filename+'_web.jpg'
	urlretrieve("http://192.168.6.4",path)
	f = open(path, mode='rb')
	global image
	image = f.read()
	f.close()

def scan_item(item):
	"""
  	Updates the "taken"-status of the scanned item in the database.
 	"""
	db = sqlite3.connect('/home/cbm66/Desktop/box.db')
	cursor = db.cursor()
	cursor.execute("Update items set taken = case when taken = 0 then 1 else 0 end where qrcode=" + "\'"  +  str(item)+ "\'")
	db.commit()
	db.close()

	
def on_press(key):
	"""
 	Catches the input of the qr-code-scanner.
  	Appends all letters, numbers etc. and calls scan_item() to update the database
 	"""
	if opened:
		try:
			qr_data.append(key.char)
		except AttributeError:
			pass
		if (key == keyboard.Key.down):
			qr_code = "".join(qr_data)
			qr_codes.append(qr_code)
			print(qr_codes)
			scan_item(qr_code)
			qr_data.clear()

listener = keyboard.Listener(on_press=on_press)
listener.start()
	
def end_session():
	"""
 	Used to close the door of the 'Tech-Tresor'
	The already taken picture, session_uid and all the borrowed items are saved in the database 
	The number of all items and all available items are saved as variables
   	The if/elif/else-part is used to tell the arduino to cahnge the led color corresponding to the percantage of items in 'Tech-Tresor'
 	"""
	global qr_data, qr_codes, image, session_uid, opened
	db = sqlite3.connect('/home/cbm66/Desktop/box.db')
	cursor = db.cursor()
	cursor.execute("INSERT INTO images (image, uid, qrcodes) VALUES (:image,:uid,:qrcodes)", (image, session_uid,"|".join(qr_codes)))
	db.commit
	
	cursor.execute("SELECT COUNT(*) FROM items")
	number_all_items = cursor.fetchone()[0]
	cursor.execute("SELECT COUNT(*) FROM items WHERE taken = 0")
	number_items = cursor.fetchone()[0]
	db.close()
	percent = number_items / number_all_items
	if percent < 0.3:
		arduino.write(bytes("0", "utf-8"));
	elif percent < 0.6:
		arduino.write(bytes("1", "utf-8"));
	else:
		arduino.write(bytes("2", "utf-8"));
		
	qr_data = []
	qr_codes = []
	image = None
	session_uid = ""
	opened = False
	print("session closed")
	

	
def start_session(arduino_data):
	"""
 	Takes a picture of the interior, opens the door and changes the led colors to white
 	"""
	global opened, session_uid
	print("RFID UID:", arduino_data)
	session_uid = arduino_data
	try:
		take_picture()
	except Exception as e:
		pass	
	print("pic taken")
	arduino.write(bytes("3", "utf-8"));
	opened = True



"""
Main-function:
	The script checks whether the Arduino has transmitted a new message.
 	If there is a new message, the script either:	1. calls end_session()
  							2. plays a random sound, using the SoundThread()
	 						3. calls start_session()
"""
while True:
	arduino_data = arduino.readline(32)
	
	if len(arduino_data) > 0:
		
		print(len(arduino_data.decode("utf-8").strip()))
		if opened and len(arduino_data.decode("utf-8").strip()) > 6 and not arduino_data.decode("utf-8").strip()=="SOUND": 
			print("try close")
			end_session()
		elif arduino_data.decode("utf-8").strip()=="SOUND" and not opened:
			if sound_Thread is None or not sound_Thread.is_playing:
				print("actually playing sound")
				file_path_sound = sound_path + random.choice(file_path_sound_array)
				sound_Thread = SoundThread(file_path_sound)
				sound_Thread.start()
		elif not opened and len(arduino_data.decode("utf-8").strip()) > 6:
			start_session(arduino_data)	
			
	else:
		pass
