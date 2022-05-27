package com.test.csq.common.lang;

import com.test.csq.common.Dto.LatLng;
import com.test.csq.common.Dto.RunningRecord;
import lombok.Data;

import java.util.List;

@Data
public class ResultList {
    int code;
    String message;
    List<RunningRecord> data;

    public static ResultList res(String message, int code, List<RunningRecord> data) {
        ResultList resultList=new ResultList();
        resultList.setData(data);
        resultList.setCode(code);
        resultList.setMessage(message);
        return resultList;
    }
}
