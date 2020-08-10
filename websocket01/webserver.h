String header = "HTTP/1.1 200 OK\r\nContent-Type: text/html\r\n\r\n";
 
String html_1 = R"=====(
<!DOCTYPE html>
<html>

<style>
  body {
    background-color: #DCDCDC;
    position: center;
    top: 100px;
  }

  #main    { display: table; width: 300px; margin: auto;  padding: 10px 10px 10px 10px; border: 3px solid blue; border-radius: 10px; text-align:center;} 
  .switch {
    position: relative;
    display: inline-block;
    width: 60px;
    height: 34px;
  }

  .switch input {display:none;}

  .slider {
    position: absolute;
    cursor: pointer;
    top: 0;
    left: 0;
    right: 0;
    bottom: 0;
    background-color: #A93226;
    -webkit-transition: .4s;
    transition: .4s;
  }

  .slider:before {
    position: absolute;
    content: "";
    height: 26px;
    width: 26px;
    left: 4px;
    bottom: 4px;
    background-color: #2E4053;
    -webkit-transition: .4s;
    transition: .4s;
  }

  input:checked + .slider {
    background-color: #1E8449;
  }

  input:focus + .slider {
    box-shadow: 0 0 1px #1E8449;
  }

  input:checked + .slider:before {
    -webkit-transform: translateX(26px);
    -ms-transform: translateX(26px);
    transform: translateX(26px);
  }

  /* Rounded sliders */
  .slider.round {
    border-radius: 34px;
  }

  .slider.round:before {
    border-radius: 50%;
  }
  .center {
    margin: auto;
    width: 60%;
    border: 2px solid #85929E;
    padding: 10px;
  }
  .table {
    width: 100%;
    border-collapse: collapse !important;
  }
  .table td,
  .table th {
    padding: 5px;
    border: 1px solid #212F3D !important;
    color:  #212F3D;
  }
  .table td, th, a{
    color: #212F3D;
    text-decoration: none;
  }

</style>

<head>
  <meta name='viewport' content='width=device-width, initial-scale=1.0'/>
  <meta charset='utf-8'>
  <title>Websockets</title>
</head>

<body>
  <div id='main' class="center">
    
    <table class="table table-condensed">
    
      <h3>LIGHTING CONTROL</h3>  // you may rename the html page here
      
      <tr>
                <th style="width: 12px">#</th>
                <th>Ligth Location</th>
                <th>Status</th>
      </tr>
      
      <tr>
        <td>1.</td>
        <td>Room 1</td>  // rename this according to your load schedule
        <td>
          <label class="switch">
            <input id = "switch0" type="checkbox" onclick="if(this.checked){sendText('01')} else{sendText('00')}">
            <span class="slider round"></span>
          </label>
        </td>
          
      </tr>

      <tr>
        <td>2.</td>
        <td>Room 2</td>  // rename this according to your load schedule
        <td>
          <label class="switch">
            <input id = "switch1" type="checkbox" onclick="if(this.checked){sendText('11')} else{sendText('10')}">
            <span class="slider round"></span>
          </label>
        </td>
          
      </tr>

      <tr>
        <td>3.</td>
        <td>Living Room</td>  // rename this according to your load schedule
        <td>
          <label class="switch">
            <input id = "switch2" type="checkbox" onclick="if(this.checked){sendText('21')} else{sendText('20')}">
            <span class="slider round"></span>
          </label>
        </td>
          
      </tr>

      <tr>
        <td>4.</td>
        <td>Kitchen</td>  // rename this according to your load schedule
        <td>
          <label class="switch">
            <input id = "switch3" type="checkbox" onclick="if(this.checked){sendText('31')} else{sendText('30')}">
            <span class="slider round"></span>
          </label>
        </td>
          
      </tr>

      <tr>
        <td>5.</td>
        <td>Wash Room</td>  // rename this according to your load schedule
        <td>
          <label class="switch">
            <input id = "switch4" type="checkbox" onclick="if(this.checked){sendText('41')} else{sendText('40')}">
            <span class="slider round"></span>
          </label>
        </td>
          
      </tr>

      <tr>
        <td>6.</td>
        <td>Back Yard</td>  // rename this according to your load schedule
        <td>
          <label class="switch">
            <input id = "switch5" type="checkbox" onclick="if(this.checked){sendText('51')} else{sendText('50')}">
            <span class="slider round"></span>
          </label>
        </td>
          
      </tr>

      <tr>
        <td>7.</td>
        <td>Gate</td>  // rename this according to your load schedule
        <td>
          <label class="switch">
            <input id = "switch6" type="checkbox" onclick="if(this.checked){sendText('61')} else{sendText('60')}">
            <span class="slider round"></span>
          </label>
        </td>
          
      </tr>
          
    </table>
    
  <p>Recieved data = <span id='rd'>---</span> </p>
    <br />
   </div>
</body>
 
<script>
  var Socket;
  var data;
  function init() 
  {
    Socket = new WebSocket('ws://' + window.location.hostname + ':81/');
    Socket.onmessage = function(event) { processReceivedCommand(event); };
  }
 
 
function processReceivedCommand(evt){
    document.getElementById('rd').innerHTML = evt.data;
    var tmp = evt.data;
    if (tmp[0] ==="0") 
    {  
        if(tmp[1] === "0"){
          document.getElementById('switch0').checked = false;
        }
        if(tmp[1] === "1"){
          document.getElementById('switch0').checked = true;
        }
    }
    if (tmp[0] ==="1") 
    {  
        if(tmp[1] === "0"){
          document.getElementById('switch1').checked = false;
        }
        if(tmp[1] === "1"){
          document.getElementById('switch1').checked = true;
        }
    }
    if (tmp[0] ==="2") 
    {  
        if(tmp[1] === "0"){
          document.getElementById('switch2').checked = false;
        }
        if(tmp[1] === "1"){
          document.getElementById('switch2').checked = true;
        }
    }
    if (tmp[0] ==="3") 
    {  
        if(tmp[1] === "0"){
          document.getElementById('switch3').checked = false;
        }
        if(tmp[1] === "1"){
          document.getElementById('switch3').checked = true;
        }
    }
    if (tmp[0] ==="4") 
    {  
        if(tmp[1] === "0"){
          document.getElementById('switch4').checked = false;
        }
        if(tmp[1] === "1"){
          document.getElementById('switch4').checked = true;
        }
    }
    if (tmp[0] ==="5") 
    {  
        if(tmp[1] === "0"){
          document.getElementById('switch5').checked = false;
        }
        if(tmp[1] === "1"){
          document.getElementById('switch5').checked = true;
        }
    }
    if (tmp[0] ==="6") 
    {  
        if(tmp[1] === "0"){
          document.getElementById('switch6').checked = false;
        }
        if(tmp[1] === "1"){
          document.getElementById('switch6').checked = true;
        }
    }

}

function sendText(data){
    Socket.send(data);
}
 
 
  window.onload = function(e)
  { 
    init();
  }
</script>
 
 
</html>
)=====";
