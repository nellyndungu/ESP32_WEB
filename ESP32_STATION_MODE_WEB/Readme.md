ESP32 WEB USING STATION WiFi MODE
## Overview
In a nutshell, this project turns the ESP32 into a simple ticketing machine that runs entirely on a web page.
The ESP32 itself hosts a small website where a user can enter their name and instantly receive a ticket. 
Each ticket includes the person’s name, the time the ticket was generated, and a unique five-character ID made up of two letters from the name and three random digits. 
The ticket is neatly displayed in a card-like format and can be downloaded as a PDF for saving or sharing. 
The system highlights how an ESP32 can combine wireless networking, web hosting, and real-time data generation into one compact project.
## How it works
The ESP32 connects to the internet by joining a WiFi network using credentials written in the code. 
Once connected, it creates a lightweight web server that can be reached through the ESP32’s assigned IP address. 
By entering this IP address in a browser on the same network, the user gains access to the ticket webpage. 
From there, a simple form allows the user to input their name, which the ESP32 processes to generate a ticket.
Behind the scenes, the ESP32 manages a few technical steps: it keeps the WiFi connection alive by reconnecting if it drops, it dynamically builds the webpage content to insert the ticket details, and it generates a downloadable PDF file so the ticket can be stored.
