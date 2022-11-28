

function addMarker(coords,map){
    var marker = new google.maps.Marker({
        position:coords,
        map:map,
    });
}


// Initialize and add the map
function initMap() {
    // The location of geneva
    const geneva = { lat: 46.2017559, lng: 6.1466014 };
    // The map, centered at geneva
    const map = new google.maps.Map(document.getElementById("map"), {
        zoom: 13,
        center: geneva,
    });
    
    //Get the data from json file on the server
    fetch('http://64.225.98.10:5050/', {mode: 'cors'})
    .then(
    response => {
        if (response.status !== 200) {
        console.log('Looks like there was a problem. Status Code: ' +
            response.status);
        return;
    }

    // Examine the text in the response
    response.json()
    .then(function(data) {
        for (var key in data) {
            if (data.hasOwnProperty(key)) {
                var val = data[key];
                //addMarker({lat: val.lat, lng: val.lon},map);
                var marker = new google.maps.Marker({
                    position:{lat: val.lat, lng: val.lon},
                    map:map,
                    title: val.valeur.toString()+'db'
                });
            }
        }
    });
    })
    .catch(err => console.log('Fetch Error :-S', err));
}