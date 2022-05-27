package com.test.csq.service.impl;

import com.test.csq.common.Dto.*;
import com.test.csq.common.lang.Result;
import com.test.csq.pojo.User;
import com.test.csq.mapper.UserMapper;
import com.test.csq.service.IUserService;
import com.baomidou.mybatisplus.extension.service.impl.ServiceImpl;
import com.test.csq.utils.GetSHA256Str;
import net.sf.json.JSONArray;
import net.sf.json.JSONObject;
import net.sf.json.JsonConfig;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.data.redis.core.RedisTemplate;
import org.springframework.data.redis.core.ValueOperations;
import org.springframework.http.ResponseEntity;
import org.springframework.stereotype.Service;
import org.springframework.util.LinkedMultiValueMap;
import org.springframework.web.client.RestTemplate;
import org.springframework.web.multipart.MultipartFile;
import sun.misc.BASE64Encoder;


import java.io.File;
import java.io.IOException;
import java.nio.file.Files;
import java.util.ArrayList;
import java.util.List;
import java.util.concurrent.TimeUnit;

/**
 * <p>
 *  服务实现类
 * </p>
 *
 * @author van
 * @since 2022-01-18
 */
@Service
public class UserServiceImpl extends ServiceImpl<UserMapper, User> implements IUserService {
    @Autowired
    private UserMapper userMapper;
    @Autowired
    private RedisTemplate redisTemplate;
    @Override
    public boolean saveUserToDataBase(User user) {
        userMapper.saveUser(user);
        return true;
    }
    public void saveMessageToRedis(String phone,String tempMessage){
        ValueOperations ops = redisTemplate.opsForValue();
        ops.set(phone,tempMessage,10,TimeUnit.MINUTES);
    }

    @Override
    public void saveTokenToRedis(String token,User user) {
        ValueOperations ops=redisTemplate.opsForValue();
        ops.set(token,user,30,TimeUnit.DAYS);
    }

    @Override
    public boolean IsRepeatSend(String phone) {
        ValueOperations ops = redisTemplate.opsForValue();
        if(ops.get(phone)!=null) {
            return true;
        }
        return false;
    }

    @Override
    public String getMessageFromRedis(String phone) {
        return (String)redisTemplate.opsForValue().get(phone);
    }

    @Override
    public void saveHeadsulptureToDataBase(int id,String url) {
        userMapper.saveHeadsulpture(id,url);
    }

    @Override
    public void saveSHAtoRedis(String key, String value) {
        redisTemplate.opsForValue().set(key,value);
    }

    @Override
    public User getUserFromRedis(String token) {
        ValueOperations ops=redisTemplate.opsForValue();
        User user=(User)ops.get(token);
        return user;
    }

    @Override
    public User findPeo(String phone) {
        User user=userMapper.findPeo(phone);
        return user;

    }

    @Override
    public boolean testIMEI(String imei,User user) {
        ValueOperations ops = redisTemplate.opsForValue();
        String oldIMEI= (String) ops.get(user.getPhone());
        if(oldIMEI==null){
            return true;
        }
        String newIMEI= GetSHA256Str.getSHA256Digest(user.toString()+imei);
        return oldIMEI.equals(newIMEI);
    }

    @Override
    public void revisePassword(String phone, String password) {
        userMapper.revisePassword(phone,password);
    }

    @Override
    public String uploadPhoto(MultipartFile file) throws IOException {
        String originalFilename=file.getOriginalFilename();
        //取的新的名字就是时间戳加扩展名
        String fileName=System.currentTimeMillis()+"."+originalFilename.substring(originalFilename.lastIndexOf(".")+1);
        String filePath="/java/project/photo/";
        File dest=new File(filePath+fileName);
        //将文件从本地磁盘上传到服务器中
        if(!dest.getParentFile().exists())
            dest.getParentFile().mkdirs();
        try {
            file.transferTo(dest);
        } catch (Exception e) {
            e.printStackTrace();
        }

        RestTemplate restTemplate=new RestTemplate();
        String key="7d2bc0fd5fa028b989aaf1bcb9341dc3";
        String url="https://api.imgbb.com/1/upload";

        LinkedMultiValueMap<String,Object> map=new LinkedMultiValueMap<>();
        final byte[] bytes= Files.readAllBytes(dest.toPath());
        final String s=new BASE64Encoder().encode(bytes);

        map.add("image",s);
        map.add("key",key);

        final ResponseEntity<String> post=restTemplate.postForEntity(url,map,String.class);

        String json_response=post.getBody();
        JSONObject jsonObject = JSONObject.fromObject(json_response);

        JSONObject data = JSONObject.fromObject(jsonObject.get("data").toString());
        JSONObject image = JSONObject.fromObject(data.get("image"));

        return (String)image.get("url");
    }

    @Override
    public Result saveRoad(RunningRecord runningRecord) {
        List<LatLng> receive=runningRecord.getPathPointsLine();
        //将list转化为json数组
        JSONArray jsonArray=JSONArray.fromObject(receive);
        String json=jsonArray.toString();
        userMapper.saveRoad(json,runningRecord.getDistance(),runningRecord.getRunningtime(),runningRecord.getStartTime(),runningRecord.getCalorie(),runningRecord.getSpeed(),runningRecord.getDistribution(),runningRecord.getUsername());
        return Result.res(null,500,"保存成功");
    }

    @Override
    public List<RunningRecord> getRoad(String Username) {
        List<Road1> listRoad=userMapper.getRoad(Username);
       List<RunningRecord> listRunningRecord=new ArrayList<>();
       for(int i=0;i<listRoad.size();i++) {
           String s=listRoad.get(i).getLocaltion();
           JSONArray jsonArray = JSONArray.fromObject(s);
           //将路线转化为list
           List<LatLng> list=JSONArray.toList(jsonArray,new LatLng(),new JsonConfig());
           RunningRecord runningRecord=new RunningRecord();
           //将road1中的信息全部转到runningRecord中
           runningRecord.setCalorie(listRoad.get(i).getCalorie());
           runningRecord.setDistance(listRoad.get(i).getDistance());
           runningRecord.setDistribution(listRoad.get(i).getDistribution());
           runningRecord.setPathPointsLine(list);
           runningRecord.setRunningtime(listRoad.get(i).getRunningtime());
           runningRecord.setSpeed(listRoad.get(i).getSpeed());
           runningRecord.setStartTime(listRoad.get(i).getStartTime());
           runningRecord.setUsername(Username);

            listRunningRecord.add(runningRecord);
       }
       return listRunningRecord;
    }

    @Override
    public boolean existsUser(String username) {
        List<User> list=userMapper.findPeoByUser(username);
        if(list!=null)
            return true;
        return false;
    }

    @Override
    public void saveGoodsInformation(String url, String discribe) {
        userMapper.saveGoodsInformation(url,discribe);
    }

    @Override
    public void saveInfo(String sex, int high, int weight, String signature, long birthday,int id) {
        userMapper.saveInfo(sex,high,weight,signature,birthday,id);
    }

    @Override
    public boolean upLoadCommunity(CommunityDto communityDto) {
        List<Picture> pictures=communityDto.getPicture();
        //将list转化为json数组
        JSONArray jsonArray=JSONArray.fromObject(pictures);
        String json=jsonArray.toString();

        List<Picture> pictureList=communityDto.getRePicture();
        JSONArray jsonArray1=JSONArray.fromObject(pictureList);
        String json1=jsonArray1.toString();
        userMapper.upLoadCommunity(communityDto.getAuthor(),communityDto.getContent(),communityDto.getTime(),communityDto.getAvatar(),json,communityDto.getReContent(),communityDto.getReAuthor(),json1);
        return true;
    }

    @Override
    public List<CommunityDto> getCommunity() {
        List<GetCommunity> list=userMapper.getCommunity();
        List<CommunityDto> communityDtoList=new ArrayList<>();

        for(int i=0;i<list.size();i++) {
            String s1=list.get(i).getPicture();
            String s2=list.get(i).getRePicture();
            //将两个picture的json字符串转换为数组
            JSONArray jsonArray=JSONArray.fromObject(s1);
            List<Picture> list1=JSONArray.toList(jsonArray,new Picture(),new JsonConfig());

            JSONArray jsonArray1=JSONArray.fromObject(s2);
            List<Picture> list2=JSONArray.toList(jsonArray1,new Picture(),new JsonConfig());

            CommunityDto communityDto=new CommunityDto();
            communityDto.setAuthor(list.get(i).getAuthor());
            communityDto.setContent(list.get(i).getContent());
            communityDto.setTime(list.get(i).getTime());
            communityDto.setAvatar(list.get(i).getAvatar());
            communityDto.setPicture(list1);
            communityDto.setReContent(list.get(i).getReContent());
            communityDto.setReAuthor(list.get(i).getReAuthor());
            communityDto.setRePicture(list2);

            communityDtoList.add(communityDto);
        }
        return communityDtoList;

    }
}
