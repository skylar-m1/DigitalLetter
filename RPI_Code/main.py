import serial
import time
from flask import Flask, request, render_template

app = Flask(__name__, template_folder="templates")
baudRate = 9600
interface = 'COM4'
arduino = serial.Serial(interface, baudRate, timeout=0) 
def writeData(x): 
    try:

        if arduino.is_open:
            arduino.write((str(x) + '\n').encode('utf-8')) 
            print(f"[*] Wrote message: {x}")
    except serial.SerialException as e:
      print(f"Error: {e}")



@app.route('/message', methods=['GET', 'POST'])
def writeMessage():
    if (request.method == 'POST'):

        message = request.form["user_text"]
        writeData(message)
        #print(message)

    return render_template("main.html")


    

if __name__ == '__main__':

    app.run(debug=True)