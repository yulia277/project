package com.test.csq.service;

import com.test.csq.common.Dto.CommunityDto;
import com.test.csq.common.Dto.RunningRecord;
import com.test.csq.common.lang.Result;
import com.test.csq.pojo.User;
import com.baomidou.mybatisplus.extension.service.IService;
import org.springframework.web.multipart.MultipartFile;

import java.io.IOException;
import java.util.List;

/**
 * <p>
 *  服务类
 * </p>
 *
 * @author van
 * @since 2022-01-18
 */
public interface IUserService extends IService<User> {
    //将用户信息保存到数据库中
    public boolean saveUserToDataBase(User user);
    //将短信保存在数据库中，设置十分钟过期
    public void saveMessageToRedis(String phone,String tempMessage);
    //将token保存在redis中，每次登录会更新时间
    public void saveTokenToRedis(String token,User user);
    //判断短信是否重复发送
    public boolean IsRepeatSend(String phone);
   //从redis中获得用户信息
    public String getMessageFromRedis(String phone);
    //保存用户头像
    public void saveHeadsulptureToDataBase(int id,String url);
    public void saveSHAtoRedis(String key,String value);
    //根据token获得用户的id
    public User getUserFromRedis(String token);
    //根据手机查找用户
    public User findPeo(String phone);
    boolean testIMEI(String imei,User user);
    //重新设置密码
    public void revisePassword(String phone,String password);
    //上传图片
    public String uploadPhoto(MultipartFile file) throws IOException;
    //保存路径
    public Result saveRoad(RunningRecord runningRecord);
    //获得路径
    public List<RunningRecord> getRoad(String Username);
    //判断用户是否存在
    public boolean existsUser(String username);
    //将商品的图片和信息存到数据库中
    public void saveGoodsInformation(String url,String discribe);
    //将用户的其他信息保存在数据库中
    public void saveInfo(String sex,int high,int weight,String signature,long birthday,int id);
    public boolean upLoadCommunity(CommunityDto communityDto);
    public List<CommunityDto> getCommunity();
}
