package com.test.csq.common.Dto;

import lombok.Data;

import java.util.List;

@Data
public class CommunityDto {
    String author;
    String content;
    String time;
    String avatar;
    List<Picture> picture;
    String reContent;
    String reAuthor;
    List<Picture> rePicture;

}
