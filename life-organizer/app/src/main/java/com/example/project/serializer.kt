package com.example.project

import org.json.JSONObject
import org.json.JSONException

class Serializer {
    val data: MutableMap<String, String> = mutableMapOf()
    var valid: Boolean = true

    constructor(body: String?) {
        try {
            var reader = JSONObject(body)
                .getJSONObject("contents")
                .getJSONArray("quotes")[0]
            var dict = JSONObject(reader.toString())
            data.put("quote", dict.getString("quote"))
            data.put("author", dict.getString("author"))
            data.put("date", dict.getString("date"))
        } catch (err: JSONException) {
            valid = false
        }

    }
}