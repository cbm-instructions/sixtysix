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

arduino = serial.Serial(port='/dev/ttyACM0', baudrate=9600, timeout=.1)
qr_scanner = serial.Serial(port='/dev/ttyAMA0', baudrate= 9600, timeout=1)
qr_scanner.reset_input_buffer()
qr_data = []
qr_codes = []
image = None
session_uid = ""
opened = False
sound_path = '/home/cbm66/Desktop/Sounds/'
file_path_sound_array = ['willst_teile.mp3', 'gutes_zeug.mp3', 'letzte_chance.mp3', 'fluestern_brauchst_teile.mp3']

class SoundThread(threading.Thread):
	def __init__ (self, file_path):
		super().__init__()
		self.file_path=file_path
		self.is_playing = False
		self.daemon = True
		
	def run(self):
		pygame.mixer.music.load(self.file_path)
		pygame.mixer.music.play()
		
		self.is_playing = True
		while pygame.mixer.music.get_busy():
			continue
		
		time.sleep(60)
		self.is_playing = False	
		
sound_Thread = None
		
def play_sound(path):
	pygame.mixer.music.load(path)
	pygame.mixer.music.play()
	while pygame.mixer.music.get_busy() == True:
		continue
	
	
def take_picture():
	filename = str(datetime.datetime.now().timestamp()) + "_pic"
	path = '/home/cbm66/Desktop/pics/' + filename+'_web.jpg'
	urlretrieve("http://192.168.6.4",path)
	f = open(path, mode='rb')
	global image
	image = f.read()
	f.close()

def scan_item(item):
	db = sqlite3.connect('/home/cbm66/Desktop/box.db')
	cursor = db.cursor()
	cursor.execute("Update items set taken = case when taken = 0 then 1 else 0 end where qrcode=" + "\'"  +  str(item)+ "\'")
	db.commit()
	db.close()

	
def on_press(key):
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
	global qr_data, qr_codes, image, session_uid, opened
	db = sqlite3.connect('/home/cbm66/Desktop/box.db')
	cursor = db.cursor()
	cursor.execute("INSERT INTO images (image, uid, qrcodes) VALUES (:image,:uid,:qrcodes)", (image, session_uid,"|".join(qr_codes)))
	db.commit()
	cursor.execute("SELECT COUNT(*) FROM items")
	number_all_items = cursor.fetchone()[0]
	cursor.execute("SELECT COUNT(*) FROM items WHERE taken = 0")
	number_items = cursor.fetchone()[0]
	db.close()
	percent = number_items / number_all_items
	print(percent)
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
