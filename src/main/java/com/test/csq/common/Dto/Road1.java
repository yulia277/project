package com.test.csq.common.Dto;

import lombok.Data;

@Data
public class Road1 {
    private Long id;
    //运动轨迹
    //表示这是数据库表中的一个列。其中的name表示此对象在表中对应的类名，
    // 如果不添加此注解，Room默认会以此变量名作为其在表中的列名。
    private String localtion;
    //运动距离
    private String distance;
    //运动时长
    private Long runningtime;
    //运动开始时间
    private String startTime;
    //消耗卡路里
    private String calorie;
    //平均时速(公里/小时)
    private String speed;
    //平均配速(分钟/公里)
    private Double distribution;
    private String username;
}
