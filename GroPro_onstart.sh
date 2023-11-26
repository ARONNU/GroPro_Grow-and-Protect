#My virtual Environment With The Visual Object Detection Code
source /home/aronn/onnx2/venv/bin/activate
cd /home/aronn/onnx2
python3 visual_detect_demo.py

#To send the detected string data to arduino
cd /home/aronn/GroPro_Files/
sudo python3 arduino_transfer2.py

#For Sound Object Detection
cd /home/aronn/GroPro_Files/
sudo python3 audio_detect.py

#To send the detected string data to arduino
cd /home/aronn/GroPro_Files/
sudo python3 arduino_transfer2.py

#Clearing the text file  
cd /home/aronn/GroPro_Files/
python3 reset.py
