package com.example.ssl2

import android.app.PendingIntent
import android.content.Intent
import android.content.IntentFilter
import android.nfc.NfcAdapter
import android.nfc.NfcAdapter.ACTION_NDEF_DISCOVERED
import android.nfc.NfcAdapter.ACTION_TECH_DISCOVERED
import android.nfc.Tag
import android.nfc.tech.IsoDep
import android.nfc.tech.TagTechnology
import android.os.Bundle
import android.text.Html
import android.widget.TextView
import android.widget.Toast
import androidx.appcompat.app.AppCompatActivity
import android.nfc.tech.MifareClassic
import android.util.Log
import com.google.firebase.firestore.FieldValue
import com.google.firebase.firestore.FirebaseFirestore
import java.util.*


const val MIME_TEXT_PLAIN = "text/plain"

class ScanLuggage : AppCompatActivity() {


    private var nfcAdapter: NfcAdapter? = null

    private var isNfcSupported: Boolean = this.nfcAdapter != null

    private var txtv_result: TextView? = null

    val db = FirebaseFirestore.getInstance()
    var cheking = ""


    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setContentView(R.layout.activity_scan_luggage)
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

        this.txtv_result = findViewById(R.id.txtv_result)
        txtv_result?.text = "ID"

        cheking = intent.getStringExtra("check").toString()
    }

    override fun onNewIntent(intent: Intent) {
        super.onNewIntent(intent)

        val tag = intent.getParcelableExtra<Tag>(NfcAdapter.EXTRA_TAG)
        IsoDep.get(tag)?.let { isoDepTag ->
            Log.wtf("simulateScanCheckpoint1", isoDepTag.historicalBytes.toString())
            val response = isoDepTag.tag.id
            Log.wtf(
                "simulateScanCheckpoint22222222",
                response.toHexString()
            ) //////////////////////// ton ID est ici

            txtv_result?.text = response.toHexString()

            db.collection("Users").get()
                .addOnCompleteListener {
                    println(it)
                    if (it.isSuccessful)
                        for (doc in it.result!!) {

                            if (doc.data["luggages"] != null) {
                                val lugg = doc.data["luggages"].toString()

                                if (lugg.contains(response.toHexString())) {

                                    val nestedCheck = hashMapOf(
                                        cheking to true
                                    )

                                    val luggage = hashMapOf(
                                        "luggages" to nestedCheck
                                    )

                                    db.collection("Users").document(doc.id).update(
                                        mapOf("luggages.$cheking" to true)).addOnCompleteListener {
                                        if (it.isSuccessful) {
                                            Toast.makeText(
                                                this,
                                                "L'enregistrement à bien été fait.",
                                                Toast.LENGTH_SHORT
                                            ).show()
                                        }
                                    }
                                }
                            }
                        }
                    //Toast.makeText(this, "Found it : " + response.toHexString(), Toast.LENGTH_SHORT)
                    //.show()

                }

        }
    }

    fun ByteArray.toHexString() = joinToString("") { "%02x".format(it) }

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
            val filters = arrayOf(IntentFilter(ACTION_TECH_DISCOVERED))
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
}