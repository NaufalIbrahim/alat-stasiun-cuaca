* Proyek Stasiun cuaca mini *

Proyek ini dibuat untuk memenuhi tugas akhir mata kuliah Instrumentasi fisika

Proyek di dikerjakan secara kelompok
Nama kelompok : Siraj Naufal Ibrahim
		Mega Mustika
		Nur Jannah
		Siti Rahmawati
		Rodhy Hartayasa

* Deskripsi *

Rancang bangun alat ini membutuhkan beberapa komponen
Komponen & sensor: 	Sensor DHT11 (mengukur temperatur & kelembapan)
			Sensor BMP 280 (mengukur tekanan udara)
			Lora (Transmisi sinyal komponen utama Sender ke Receiver)
			Arduino UNO (Mikrokontroler Sender)
			ESP32 (Mikrokontroler Receiver)
			Kabel Jumper (Penghubung antara sensor ke mikrokontroler)

KOMPONEN SENDER: Arduino + Data Logger + sensor DHT11 + sensor BMP 280 + Lora(sender)
KOMPONEN RECEIVER : ESP32 + Lora(receiver) + thingspeak.io

* Cara Kerja *

Alat ini dirancang untuk mengetahui parameter" yang terkait dengan cuaca (temperatur,kelembapan,tekanan udara)

Komponen utama sender dan receiver di rentangkan pada jarak tertentu untuk mengetahui perbedaan data tiap lokasi, 
lalu hasilnya secara live di tampilkan di platform IOT thingspeak.io.

Tiap komponen utama di program/koding menggunakan software arduino IDE.

Komponen sender bergerak di setiap titik lokasi pengamatan untuk mendapatkan data dan diberi selang 1 menit untuk kalibrasi data yang diterima
sebelum bergerak ke titik berikutnya,sementara komponen receiver tetap berada di satu tempat untuk memantau data yang diterima langsung agar bisa 
ditampilkan di thingspeak.io

Untuk hasil pengukuran tiap titik lokasi dapat dilihat folder "hasil pengukuran".



 
		
				
