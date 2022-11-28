import requests
import time
import json
import base64


# Script pour la mise à jour dynamique du fichier json

headers = {
	'Authorization': 'Bearer [API AUTH KEY]',
	'Accept': 'text/event-stream',
}

while True:
	r=requests.get('https://eu1.cloud.thethings.network/api/v3/as/applications/asm-sonore-test/packages/storage/uplink_message', headers=headers)
	decoded = r.content.decode()
	lines = decoded.split('\n')
	line = lines[-3] # last info
	print(line)
	try:
		ttn_json = json.loads(line)
		msg = ttn_json['result']['uplink_message']['frm_payload']
		msg = base64.b64decode(msg)
		print(msg)
	except Exception as e:
		print('! ', e)
	try:
		j = None
		with open('./test.json', 'r') as f:
			j = json.load(f)
			j[0]['valeur'] = int.from_bytes(msg, 'big')
		with open('./test.json', 'w') as f:
			json.dump(j, f)
	except Exception as e:
		print('!! ', e)
	time.sleep(30)


