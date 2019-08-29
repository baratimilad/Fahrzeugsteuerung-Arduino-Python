import os
import bluetooth
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

def open_img():
	# Einfügen vom Logo der HM
	logo = PhotoImage(file="~/Schreibtisch/Python/Logo.png")
	w1 = Label(root, justify=RIGHT ,image=logo).pack(side="right", expand = "yes") 

def normal_widget(root):
	explanation = '''Bluetooth GUI für Projekt Mechatronik'''
	w2 = Label(root, justify=LEFT, padx= 10, text=explanation).pack(side="left")

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
		btn_send = Button(self, text="Send Information", command=self.send_info)
		btn_send.grid(column=1, row=0)
		btn = Button(self, text="Quit", bg="white", fg="black", command=self.quit_GUI)
		btn.grid(column=2, row=0)
		#btn.place(x=5, y=5) -> Lieber mit Zeilen und Spalten arbeiten.

	def quit_GUI(self):
		exit()

	def send_info(self):
		print ("Send information to the HC-05")
		datenpaket = "A"
		# Mit dem Befehl wird ein ASCII Code an den seriellen Monitors des
		# Arduino geschickt. -> Beide Geräte müssen verbunden sein,
		# sonst wird eine Exception geworfen.
		#self.sock.send(datenpaket)

	def bluetooth_search(self):
		print ("Bluetooth Geräte suchen...")
		print ("")
		'''
		devices = bluetooth.discover_devices()
		
		print ("Das entsprechende Gerät bitte auswählen")
		for i in devices:
			print (bluetooth.lookup_name(i))
		
		selection = input - 1
		bt_adress = devices[selection]
		'''

		
def main():
	print ("Python GUI gestartet...")
	# Widget für die Titelseite und zur Verfügungstellung vom Fenstermanager
	root = Tk()
	root.geometry("600x400")
	#normal_widget(root)
	app = Window(root)
	

	# Damit das Fenster offen bleibt wird der untere Befehl ausgeführt.
	root.mainloop()

if __name__ == '__main__':
	main()



