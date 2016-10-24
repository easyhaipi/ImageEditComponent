//
//  QPAuth.h
//  QPLive
//
//  Created by zhangwx on 16/4/13.
//  Copyright © 2016年 Alibaba Video Cloud. All rights reserved.
//

#import <Foundation/Foundation.h>

@interface QPAuth : NSObject

+ (instancetype)shared;

/**
 * @param appKey    应用App Key
 * @param appSecret 应用App Secret
 * @param space     申请的授权空间名，命名规则：字母（区别大小写）+数字+特殊字符(短横线"-"，下划线"_"，点".")，长度限制在3-32之间
 授权成功后，视频将上传到对应文件夹。每个用户分配一个空间。
 */
- (void)registerAppWithKey:(NSString *)key secret:(NSString *)secret space:(NSString *)space success:(void(^)(NSString *accessToken))success failure:(void(^)(NSError *error))failure;

@end
