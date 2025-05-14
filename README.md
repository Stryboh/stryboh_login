 - Flash arduino_rfid_checker.ino

 - Edit service file, change username, path to script

```bash
sudo cp stryboh_login.service /etc/systemd/system/stryboh_login.service

mkdir ~/.config/stryboh-login

cp main.py ~/.config/stryboh-login/main.py

sudo chmod +x ~/.config/stryboh-login/main.py

sudo systemctl enable stryboh_par.service
```

![[Circuit-Diagram.jpg]]