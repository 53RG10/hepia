package com.example.ssl2

import android.app.PendingIntent
import android.content.Intent
import android.content.IntentFilter
import android.nfc.NfcAdapter
import android.nfc.Tag
import android.nfc.tech.IsoDep
import android.os.Bundle
import android.util.Log
import android.widget.Button
import android.widget.TextView
import android.widget.Toast
import com.google.android.material.floatingactionbutton.FloatingActionButton
import com.google.android.material.snackbar.Snackbar
import androidx.appcompat.app.AppCompatActivity
import com.google.firebase.firestore.FieldValue
import com.google.firebase.firestore.FirebaseFirestore
import com.google.firebase.firestore.SetOptions
import java.util.*

class CheckLuggage : AppCompatActivity() {

    private var nfcAdapter: NfcAdapter? = null
    private var isNfcSupported: Boolean = this.nfcAdapter != null
    private var txtv_result: TextView? = null
    val db = FirebaseFirestore.getInstance()
    var response: ByteArray? = null
    var idUser: String = ""


    fun ByteArray.toHexString() = joinToString("") { "%02x".format(it) }

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setContentView(R.layout.activity_check_luggage)
        setSupportActionBar(findViewById(R.id.toolbar))

        this.nfcAdapter = NfcAdapter.getDefaultAdapter(this)

        this.isNfcSupported = this.nfcAdapter != null

        if (!isNfcSupported) {
            Toast.makeText(this, "Nfc is not supported on this device", Toast.LENGTH_SHORT).show()
            finish()
        }

        if (!nfcAdapter!!.isEnabled) {
            Toast.makeText(
                this,
                "NFC disabled on this device. Turn on to proceed",
                Toast.LENGTH_SHORT
            ).show()
        }

        this.txtv_result = findViewById(R.id.txtv_info_scan)

        val btnAddLuggage = findViewById<Button>(R.id.btn_add_luggage)
        btnAddLuggage.setOnClickListener {


            if (response != null && idUser.isNotBlank()) {

                db.collection("Users").document(idUser).update(
                    "luggages", LuggageData(id = response?.toHexString())
                )
            }
        }
    }

    override fun onNewIntent(intent: Intent) {
        super.onNewIntent(intent)

        val tag = intent.getParcelableExtra<Tag>(NfcAdapter.EXTRA_TAG)
        IsoDep.get(tag)?.let { isoDepTag ->
            Log.wtf("simulateScanCheckpoint1", isoDepTag.historicalBytes.toString())
            response = isoDepTag.tag.id

            var txtInfoScan = findViewById<TextView>(R.id.txtv_info_scan)
            txtInfoScan.text = response!!.toHexString()
        }
    }

    override fun onResume() {
        super.onResume()

        NfcAdapter.getDefaultAdapter(this)?.let { nfcAdapter ->
            // An Intent to start your current Activity. Flag to singleTop
            // to imply that it should only be delivered to the current
            // instance rather than starting a new instance of the Activity.
            val launchIntent = Intent(this, this.javaClass)
            launchIntent.addFlags(Intent.FLAG_ACTIVITY_SINGLE_TOP)

            // Supply this launch intent as the PendingIntent, set to cancel
            // one if it's already in progress. It never should be.
            val pendingIntent = PendingIntent.getActivity(
                this, 0, launchIntent, PendingIntent.FLAG_CANCEL_CURRENT
            )

            // Define your filters and desired technology types
            val filters = arrayOf(IntentFilter(NfcAdapter.ACTION_TECH_DISCOVERED))
            val techTypes = arrayOf(arrayOf(IsoDep::class.java.name))

            // And enable your Activity to receive NFC events. Note that there
            // is no need to manually disable dispatch in onPause() as the system
            // very strictly performs this for you. You only need to disable
            // dispatch if you don't want to receive tags while resumed.
            nfcAdapter.enableForegroundDispatch(
                this, pendingIntent, filters, techTypes
            )
        }
    }


    override fun onStart() {
        super.onStart()
        val txtv_luggage_state = findViewById<TextView>(R.id.txtv_luggage_states)

        idUser = intent.getStringExtra("idUser").toString()

        if (idUser.isNullOrBlank())
            Toast.makeText(this, "L'user ID est introuvable", Toast.LENGTH_SHORT).show()

        val docRef = db.collection("Users").document(idUser.toString()).get().addOnSuccessListener {
            txtv_luggage_state.text = ""
            it?.get("luggages")?.let {
                if (it.toString().isNotBlank()) {
                    txtv_luggage_state.text = it.toString()
                }else{
                    txtv_luggage_state.text = "Aucun bagage enregistrer !"
                }
            }
        }
    }
}