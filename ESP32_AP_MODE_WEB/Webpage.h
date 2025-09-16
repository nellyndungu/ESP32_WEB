const char MAIN_page[] PROGMEM = R"rawliteral(
<!DOCTYPE html>
<html>
<head>
  <title>ESP32 Ticket System</title>
  <style>
    body { font-family: Arial, sans-serif; text-align: center; margin: 30px; }
    .card {
      display: inline-block;
      border: 2px solid #333;
      border-radius: 10px;
      padding: 20px;
      margin-top: 20px;
      width: 300px;
      box-shadow: 2px 2px 10px rgba(0,0,0,0.2);
    }
    .btn {
      margin-top: 20px;
      padding: 10px 20px;
      background: #0078D7;
      color: white;
      border: none;
      border-radius: 6px;
      cursor: pointer;
    }
  </style>
</head>
<body>
  <h2>ESP32 Ticket Generator</h2>
  <form action="/generate" method="GET">
    <label>Enter Name:</label><br><br>
    <input type="text" name="name" required>
    <br><br>
    <button class="btn" type="submit">Generate Ticket</button>
  </form>
</body>
</html>
)rawliteral";

// Function to generate HTML ticket
String generateTicketHTML(String name, String id, String time) {
  String html = R"rawliteral(
  <!DOCTYPE html>
  <html>
  <head>
    <title>ESP32 Ticket</title>
    <style>
      body { font-family: Arial, sans-serif; text-align: center; margin: 30px; }
      .card {
        display: inline-block;
        border: 2px solid #333;
        border-radius: 10px;
        padding: 20px;
        margin-top: 20px;
        width: 300px;
        box-shadow: 2px 2px 10px rgba(0,0,0,0.2);
      }
      .btn {
        margin-top: 20px;
        padding: 10px 20px;
        background: #0078D7;
        color: white;
        border: none;
        border-radius: 6px;
        cursor: pointer;
      }
    </style>
  </head>
  <body>
    <h2>ESP32 Ticket</h2>
    <div class="card">
      <p><b>Name:</b> )rawliteral" + name + R"rawliteral(</p>
      <p><b>Time:</b> )rawliteral" + time + R"rawliteral(</p>
      <p><b>ID:</b> )rawliteral" + id + R"rawliteral(</p>
    </div>
    <br>
    <form action="/" method="GET">
      <button class="btn">New Ticket</button>
    </form>
  </body>
  </html>
  )rawliteral";
  return html;
}
