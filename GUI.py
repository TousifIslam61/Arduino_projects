import tkinter as tk
import serial
import threading

arduino = serial.Serial('COM3', 9600) 
arduino.timeout = 1

def read_arduino():
    while True:
        try:
            line = arduino.readline().decode().strip()
            if line:
                update_gui(line)
        except:
            pass

def update_gui(data):
    
    print(data)  
    
    if "Soil Reading" in data:
        soil_value = int(data.split(":")[1].strip())
        soil_moisture_label.config(text=f"Soil Moisture: {soil_value}")
    
    if "Soil is dry" in data:
        soil_status_label.config(text="Soil Status: Dry", fg="red")
        
    elif "Soil is moist" in data:
        soil_status_label.config(text="Soil Status: Moist", fg="green")
    
    if "Water is enough" in data:
        water_status_label.config(text="Water Tank: Enough", fg="green")
        
    elif "Water is less" in data:
        water_status_label.config(text="Water Tank: Low! Fill It", fg="red")


root = tk.Tk()
root.title("Vertical Farm Monitor")

soil_moisture_label = tk.Label(root, text="Soil Moisture: ---", font=("Arial", 18))
soil_moisture_label.pack(pady=10)

soil_status_label = tk.Label(root, text="Soil Status: ---", font=("Arial", 18))
soil_status_label.pack(pady=10)

water_status_label = tk.Label(root, text="Water Tank: ---", font=("Arial", 18))
water_status_label.pack(pady=10)


thread = threading.Thread(target=read_arduino)
thread.daemon = True
thread.start()

root.mainloop()