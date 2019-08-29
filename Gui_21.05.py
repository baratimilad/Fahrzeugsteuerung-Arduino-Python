import os
import bluetooth
import time
import array
import matplotlib.pyplot as plt
import math
import csv
from tkinter import *


''' 	Gui über Python: Ubuntu 18.04
    	
	1. python installieren -> sudo apt install python
	2. pip installieren für Python3 und Python2
	   -> sudo apt install python3-pip
	   -> sudo apt install python-pip
	3. Bluetooth Pakete installieren: 
	   -> sudo apt-get install bluetooth libbluetooth-dev
	4. Python Bluetooth Pakete installieren:
	   -> Das ist nötig, damit import bluetooth funktioniert.
	   -> sudo python3 -m pip install pybluez
	5. Modul bluetooh kann nun verwendet werden.
	6. Für die Gui zusätzlich etwas installiert werden.
	   -> sudo apt-get install python3-tk
	7. TK-Toolkit installieren
	   -> sudo apt install python-tk
	8. Nun funktioniert auch das Module tkinter
	9. Python3 : tkinter, Python2 : Tkinter
'''
port = 1

#hier besser relativer Pfad (alle Teststrecken auf dem Laufwerk speichern)
textdatei1 = "/home/barati/Schreibtisch/Milad/Hochschule/Master/Projekt Mechatronik/Projekt Mechatronik/Teststrecken/text1.txt"
textdatei2 = "/home/barati/Schreibtisch/Milad/Hochschule/Master/Projekt Mechatronik/Projekt Mechatronik/Teststrecken/text2.txt"
textdatei3 = "/home/barati/Schreibtisch/Milad/Hochschule/Master/Projekt Mechatronik/Projekt Mechatronik/Teststrecken/text3.txt"
textdatei4 = "/home/barati/Schreibtisch/Milad/Hochschule/Master/Projekt Mechatronik/Projekt Mechatronik/Teststrecken/text4.txt"
textdatei5 = "/home/barati/Schreibtisch/Milad/Hochschule/Master/Projekt Mechatronik/Projekt Mechatronik/Teststrecken/text5.txt"
textdatei6 = "/home/barati/Schreibtisch/Milad/Hochschule/Master/Projekt Mechatronik/Projekt Mechatronik/Teststrecken/text6.txt"



global test_strecken
test_strecken = ([textdatei1, textdatei2, textdatei3, textdatei4, textdatei5, textdatei6])

class Window(Frame):

	sock = bluetooth.BluetoothSocket(bluetooth.RFCOMM)		

	def __init__(self,master = None):
		Frame.__init__(self,master)
		self.master = master

		''' Socket ist wichtig für die Bluetooth Verbindung. '''
		#self.sock.connect((bd_addr, port))
		# Muss initalisiert werden, sonst wird Methode in der Klasse nicht
		# gefunden. -> alle Methoden müssen daher vorher initialisert werden.
		# self.whatever() 
		self.init_window()
	
	# Die Methode an sich: Titel und ein Button in der Methode initialisiert.
	def init_window(self):
		self.master.title("Bluetooth GUI - Projekt Mechatronik")
		# Damit der Titel auch wie oben ist, muss mit self.pack()
		# der Text in die GUI eingebettet werden.
		self.pack(fill=BOTH, expand=1)
		# command = self.call_something() -> Eine Aktion wird gestartet, 
		# wenn der Button gedrückt wird. Wenn der Button gedrückt wird,
		# können beispielsweise Messdaten angefordert werden.
		search_bt = Button(self, text="Bluetooth suchen", command=self.bluetooth_search)
		search_bt.grid(column=0, row=0)

		btn_send = Button(self, text="Ablaufsteuerung", command=self.send_info)
		btn_send.grid(column=1, row=0)

		btn = Button(self, text="Programm beenden", bg="white", fg="black", command=self.quit_GUI)
		btn.grid(column=4, row=0)
		#btn.place(x=5, y=5) -> Lieber mit Zeilen und Spalten arbeiten.

		# Versuchskanninchen Button		
		try_btn = Button(self, text="Ablauf Test", command=self.new_frame)
		try_btn.grid(column=0, row=1)
		
		mess_btn = Button(self, text="Messdaten auslesen", command=self.messdaten)
		mess_btn.grid(column=3, row=0)

		global btlabel #this label shows which device is connected
		btlabel=Label(self, text='not connected')
		btlabel.grid(column=10,row=0)
		# Frame ausprobieren:
		''' bg=Background -> Nach RGB Muster -> '#000000' ist schwarz. '''
		frame = Frame(self, bg='#000000', bd=10)
		# relx ist für Verschiebung der x Achse verantwortlich!
		# rely für die Verschiebung der y Achse!
		# relwidth=Breite, relheight=Höhe
		frame.place(relx=0.75, rely=0.50, relwidth=0.50, relheight=0.50, anchor='n')
		global label
		label = Label(frame, bg="yellow")
		label.place(relwidth=1, relheight=1)
		new_label = Label(frame, justify=CENTER, bg = "yellow")
		new_label['text'] = "Messdaten"
		new_label.pack(anchor= "n")#benenn mal deine variablen richtig




		
		
	# Website: http://effbot.org/tkinterbook/label.htm
	def new_frame(self):
		global new_frame
		new_frame = Frame(self, bg = "grey", bd=10)
		new_frame.place(relx=0.25, rely=0.50, relwidth=0.5, relheight=0.50, anchor='n')
		new_label = Label(new_frame, justify=CENTER)
		new_label.place(relwidth=1, relheight=1)
		new_label['text'] = "Mögliche Teststrecken"
		new_label.pack(anchor= "n")
		tk1 = Label(new_frame, text="1.Teststrecke: xxx")
		tk1.pack(anchor = 'w')
		tk2 = Label(new_frame, text="2.Teststrecke: xxx")
		tk2.pack(anchor = 'w')
		tk3 = Label(new_frame, text="3.Teststrecke: xxx")
		tk3.pack(anchor = 'w')
		tk4 = Label(new_frame, text="4.Teststrecke: xxx")
		tk4.pack(anchor = 'w')
		tk5 = Label(new_frame, text="5.Teststrecke: xxx")
		tk5.pack(anchor = 'w')
		tk6 = Label(new_frame, text="6.Teststrecke: xxx")
		tk6.pack(anchor = 'w')
		tkleer = Label(new_frame, text = "", bg= "grey")
		tkleer.pack(anchor = 'sw')
		tkeingabe = Label(new_frame, text = "Ihre Strecke: ")
		tkeingabe.pack(anchor = 'sw')
		global eingabe
		eingabe = Entry(new_frame, bd=2)
		eingabe.place(x = 100, y = 165)
		btn_eingabe = Button(new_frame, text="OK", command=self.new_frame_read)
		btn_eingabe.place(x = 280, y = 162) 
		test_auswahl_leer = Label(new_frame, text="", bg = "grey")
		test_auswahl_leer.pack(anchor = 'sw')
		
	def new_frame_read(self):
		test_value = int(eingabe.get())
		eingabe_string = "Sie haben folgende Strecke ausgewählt: " + eingabe.get()
		false_value = "Strecke " + eingabe.get() + " existiert nicht. Bitte gültige Strecke angeben."
		eingabe.delete(0, 'end')
		test_auswahl= Label(new_frame)
		if (1 <= test_value <= 6):
			test_auswahl["text"] = eingabe_string
			test_auswahl.pack(anchor = 'sw')
			#if test_value  == 1:
			fobj = open(test_strecken[test_value-1], "r")
			for zeile in fobj:
   				print(zeile) # rstrip() entfernt Leerzeichen etc.
					# Überlegung: Hier schon den Inhalt der Datei an die serielle Schnittstelle des Arduino schicken? oder als string returnen und dann auswerten???
			fobj.close()
		else:
			test_auswahl["text"] = false_value
			test_auswahl.pack(anchor = 'sw')		

	def messdaten(self):
		print ("Messdaten auslesen...")
		#y1 = x1.get()
		label['text'] = "Messdaten..."
		
	def quit_GUI(self):
		exit()

	def send_info(self):
		print ("Sende Informationen an das HC-05")
		vorwärts = ("hallo*I")
		aus=("hallo+I")
		ruckwärts=("hallo,I")
		# Mit dem Befehl wird ein ASCII Code an den seriellen Monitors deseee
		# sonst wird eine Exception geworfen.
		self.sock.send(vorwärts)
		time.sleep(3)
		self.sock.send(aus)
		time.sleep(1)
		self.sock.send(ruckwärts)
		time.sleep(3)
		self.sock.send(aus)
			
	def bluetooth_search(self):
		print ("Bluetooth Geräte suchen...")
		print ("")
		devices = bluetooth.discover_devices()

		num = 0
		for i in devices:
			num+=1
			print (num , ": " , bluetooth.lookup_name( i ))
		print ("Das entsprechende Gerät bitte auswählen: ")
		selection = int(input("> ")) - 1
		bt_adress = devices[selection]
		nameofselecteddevice=bluetooth.lookup_name(devices[selection])
		print ("Verbindung mit ", nameofselecteddevice,"wird hergestellt...")
		print("")
		try:
			self.sock.connect((bt_adress, port))
			print("connection was successful")
			btlabel['text']=nameofselecteddevice
		except OSError:
			print('Shame on bluetooth! Connection wasnt successful')
		
		#data="1"
		#send = self.sock.send(data)
		
		#print ("Sie schicken folgende Nachricht an: ", send)
		
	# Methode ermöglicht eine Texteingabe!
	def entry_smth(self):
		#print ("Hi")
		entry =	Entry(self, bd=3)
		# eine andere Methode um den Standort von Entry zu setzen!
		#entry.place(relwidth=0.5, relheight=0.25)
		entry.grid(column=1, row=1)

	# End of class!


def plot_smth(): #wozu?
	plt.plot([0,1,2,3,4])
	plt.xlabel('x-Achse')
	plt.ylabel('y-Achse')
	plt.show()

		

def main():
	print ("Python GUI gestartet...")
	'''
	x = 1
	y = 1
	b = math.sum(
	rad = math.atan2(x, y)
	math.degrees(rad)
	print(b)
	print(math.degrees(rad))
	'''
	
	#plot_smth()
	# Widget für die Titelseite und zur Verfügungstellung vom Fenstermanager
	root = Tk()

	''' Schwere Geburt mit Canvas und den Bildern! '''
	#canvas = Canvas(root)
	canvas = Canvas(root, height=150, width=200)
	#canvas.pack(fill=BOTH, expand=0, anchor='center')
	canvas.pack(fill=BOTH)

	# Hintergrund der GUI
	try:
		logo = PhotoImage(file='Matrix.png')
		bg_logo = Label(root, image=logo)
		bg_logo.place(relwidth=1, relheight=1)
	except TclError:#jump in here if file not found
		print('matrix not available!')
	root.geometry("800x600")
	root.update()
	
	#img = canvas.create_image(225,225, image=logo)	
	
	#normal_widget(root)

	app = Window(root)


	# Damit das Fenster offen bleibt wird der untere Befehl ausgeführt.
	root.mainloop()

if __name__ == '__main__':
	main()


# Beispiel mit Lambda

def greetings():#wozu?
	start = ("Hallo ")
	greet = lambda x,y: start + "Herr " +str(x) if y== 'M' \
	else start + "Frau " + str(x)
	return greet

result = greetings()
#print(result("Niemand", 'M'))
	