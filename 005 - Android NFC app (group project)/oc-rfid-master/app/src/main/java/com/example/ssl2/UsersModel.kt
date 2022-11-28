package com.example.ssl2

import android.text.Editable

data class UsersData(
    val name: String,
    val address: String?,
    val login: String?,
    val password: String?,
    val luggages: List<LuggageData>?
)

data class LuggageData(
    var id: String? = "",
    var check1: Boolean? = false,
    var check2: Boolean? = false,
    var check3: Boolean? = false
)
