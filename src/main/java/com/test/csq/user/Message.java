package com.test.csq.user;

import com.test.csq.utils.HttpUtils;
import org.apache.http.HttpResponse;

import java.util.HashMap;
import java.util.Map;
import java.util.Random;

public class Message {

    public String message(String phone) {
//        return "1234";
        String host = "http://dingxin.market.alicloudapi.com";
        String path = "/dx/sendSms";
        String method = "POST";
        String appcode = "6ee84983d6b74c1d84159836c92e965a";
        Map<String, String> headers = new HashMap<String, String>();
        headers.put("Authorization", "APPCODE " + appcode);
        Map<String, String> querys = new HashMap<String, String>();
//        mobile:需发送的手机号码
        querys.put("mobile", phone);
        int code = (int) (Math.random() * 9000 + 1000);
        querys.put("param", "code:"+code);
        querys.put("tpl_id", "TP1711063");
        Map<String, String> bodys = new HashMap<String, String>();
        HttpResponse response=null;

        try {
            response = HttpUtils.doPost(host, path, method, headers, querys, bodys);

            //获取response的body
            //System.out.println(EntityUtils.toString(response.getEntity()));
        } catch (Exception e) {
            e.printStackTrace();
        }
        return String.valueOf(code);
    }
}
