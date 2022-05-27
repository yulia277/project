package com.test.csq.mapper;

import com.test.csq.common.Dto.GetCommunity;
import com.test.csq.common.Dto.Road1;
import com.test.csq.pojo.User;
import com.baomidou.mybatisplus.core.mapper.BaseMapper;
import org.apache.ibatis.annotations.Mapper;

import java.util.List;

/**
 * <p>
 *  Mapper 接口
 * </p>
 *
 * @author van
 * @since 2022-01-18
 */
@Mapper
public interface UserMapper extends BaseMapper<User> {
    public boolean saveUser(User user);
    public User findPeo(String phone);
    public List<User> findPeoByUser(String Username);
    public void saveHeadsulpture(int id,String url);
    public void revisePassword(String phone,String password);
    public void saveRoad(String json,
                         String distance,
                         Long runningtime,
                         String startTime,
                         String calorie,
                         String speed,
                         Double distribution,
                         String username);
    public List<Road1> getRoad(String Username);
    public void saveGoodsInformation(String url,String discribe);
    public void saveInfo(String sex,int high,int weight,String signature,long birthday,int id);
    public void upLoadCommunity(String author,String content,String time,String avatar,String picture,String reContent,String reAuthor,String rePicture);
    public List<GetCommunity> getCommunity();
}
