<?php 
  $user = $_GET['user']; // output 2489
  //$password = $_GET['password'];
  if($user == "axel"){
    echo "sucess";
  }else{
    header("Location: index.php");
    exit();
  }
?>
<!DOCTYPE html>
<html>
  <head>
    <meta charset="utf-8">
    <title>AMS sonore</title>

    <style type="text/css">
      /* Set the size of the div element that contains the map */
      #map {
        height: 600px;
        /* The height is 400 pixels */
        width: 100%;
        /* The width is the width of the web page */
      }
    </style>
    <script src="javascript/script.js"> </script>
  </head>
  <body>
    <h3>Geneva's noise pollution map</h3>
    <!--The div element for the map -->
    <div id="map"></div>

    <!-- Async script executes immediately and must be after any DOM elements used in callback. -->
    <script
      src="https://maps.googleapis.com/maps/api/js?key=AIzaSyDDaXfWLPfMwEP4HIp0KGei0Ho03MxAVMI&callback=initMap&libraries=&v=weekly"
      async
    ></script>
  </body>
</html>