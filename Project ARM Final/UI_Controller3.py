import gi
gi.require_version("Gtk", "3.0")
from gi.repository import Gtk
import serial

arduino = serial.Serial("/dev/ttyACM0", 9600)

class MainWindow(Gtk.Window):

	def __init__(self):
		Gtk.Window.__init__(self, title = "ARM Control")

		self.set_border_width(10)

		self.label_big_servo1 = Gtk.Label(label = 'Base Servo')
		self.label_big_servo2 = Gtk.Label(label = 'Second Servo')
		self.label_small_servo = Gtk.Label(label = 'Small Servo')
		self.label_hand = Gtk.Label(label = 'Hand')

		self.left2AngleButton = Gtk.Button("<")
		self.left2AngleButton.connect("clicked", self.left2AngleButtonAction)

		self.right2AngleButton = Gtk.Button(">")
		self.right2AngleButton.connect("clicked", self.right2AngleButtonAction)

		self.leftAngleButton = Gtk.Button("<")
		self.leftAngleButton.connect("clicked", self.leftAngleButtonAction)

		self.rightAngleButton = Gtk.Button(">")
		self.rightAngleButton.connect("clicked", self.rightAngleButtonAction)

		ad1 = Gtk.Adjustment(0, 0, 180, 5, 10, 0)
		ad2 = Gtk.Adjustment(0, 0, 180, 5, 10, 0)

		self.h_scale_2 = Gtk.Scale(orientation = Gtk.Orientation.HORIZONTAL, adjustment = ad2)
		self.h_scale_2.set_digits(0)
		self.h_scale_2.set_hexpand(True)
		self.h_scale_2.connect("value-changed", self.scale_moved_2)

		self.h_scale = Gtk.Scale(orientation = Gtk.Orientation.HORIZONTAL, adjustment = ad1)
		self.h_scale.set_digits(0)
		self.h_scale.set_hexpand(True)
		self.h_scale.connect("value-changed", self.scale_moved)

		self.label = Gtk.Label("Value: ")
		self.label_2 = Gtk.Label("Value: ")	    

		self.forwardButton = Gtk.Button(label = "^")
		self.forwardButton.connect("clicked", self.forwardButtonAction)

		self.rightButton = Gtk.Button(label = ">")
		self.rightButton.connect("clicked", self.rightButtonAction)

		self.leftButton = Gtk.Button(label = "<")
		self.leftButton.connect("clicked", self.leftButtonAction)

		self.backButton = Gtk.Button(label = "v")
		self.backButton.connect("clicked", self.backButtonAction)

		self.stopButton = Gtk.Button(label = "x")
		self.stopButton.connect("clicked", self.stopButtonAction)

		grid = Gtk.Grid()
		
		grid.add(self.label_big_servo1)
		grid.attach(self.rightAngleButton, 0, 30, 10, 10)
		grid.attach(self.leftAngleButton, 60, 30, 10, 10)

		grid.attach(self.label_big_servo2, 0, 60, 10, 10)
		grid.attach(self.right2AngleButton, 0, 90, 10, 10)
		grid.attach(self.left2AngleButton, 60, 90, 10, 10)

		grid.attach(self.label_small_servo, 0, 120, 10, 10)
		grid.attach(self.h_scale, 0, 150, 10, 10)
		grid.attach(self.label, 0, 180, 10, 10)

		grid.attach(self.label_hand, 0, 210, 10, 10)
		grid.attach(self.h_scale_2, 0, 240, 10, 10)
		grid.attach(self.label_2, 0, 270, 10, 10)
		
		grid.attach(self.forwardButton, 0, 330, 10, 10)
		grid.attach(self.leftButton, 0, 360, 10, 10)
		grid.attach(self.backButton, 60, 360, 10, 10)
		grid.attach(self.rightButton, 120, 360, 10, 10)
		grid.attach(self.stopButton, 0, 390, 10, 10)

		self.add(grid)

	def scale_moved(self, event):
		send = ""
		length = len(str(self.h_scale.get_value()))
		self.label.set_text("Value: " + str(self.h_scale.get_value()))
		send = str(length-2)+'a'+str(int(self.h_scale.get_value()))
		arduino.write(send)

	def scale_moved_2(self, event):
		send = ""
		length = len(str(self.h_scale.get_value()))
		self.label_2.set_text("Value: " + str(self.h_scale_2.get_value()))
		send = str(length - 2)+'d'+str(int(self.h_scale_2.get_value()))
		arduino.write(send)

	def forwardButtonAction(self, widget):
		arduino.write('1e1')

	def stopButtonAction(self, widget):
		arduino.write('1f1')

	def rightAngleButtonAction(self, widget):
		send = "3b750"
		arduino.write(send)

	def leftAngleButtonAction(self, widget):
		send = "4b2250"
		arduino.write(send)

	def right2AngleButtonAction(self, widget):
		send = "3c750"
		arduino.write(send)

	def left2AngleButtonAction(self, widget):
		send = "4c2250"
		arduino.write(send)

	def rightButtonAction(self, widget):
		send = "1g1"
		arduino.write(send)

	def leftButtonAction(self, widget):
		send = "1h1"
		arduino.write(send)

	def backButtonAction(self, widget):
		send = "1i1"
		arduino.write(send)

window = MainWindow()
window.show_all()
window.connect("delete-event", Gtk.main_quit)
Gtk.main()