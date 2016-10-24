//
//  QPConnectionSpeedDetector.h
//  QPConnectionSpeedDetector
//
//  Created by zhangwx on 16/3/19.
//  Copyright © 2016年 zhangwx. All rights reserved.
//

#import <UIKit/UIKit.h>
#import <Foundation/Foundation.h>


@interface QPConnectionSpeedDetector : NSObject
/**
 *  客户端IP（可选设置，默认本机ip）
 */
@property (nonatomic, copy) NSString *clientIP;
/**
 *  解析服务器地址 (可选设置，默认阿里云httpDNS）
 */
@property (nonatomic, copy) NSString *serverUrl;
/**
 *  测速端口 (可选设置, 默认80)
 */
@property (nonatomic, copy) NSString *detectPort;

/**
 *  测速
 *
 *  @param domain  主机地址
 *  @param success 成功
 *  @param failure 失败
 *  @discussion 成功result中包含所有ip及对应的speed(KB/s),按速度降序排列
 */

- (void)detectSpeedWithDomain:(NSString *)domain
                      success:(void(^)(NSArray *result))success
                      failure:(void(^)(NSError *error))failure;

/**
 *  域名解析
 *
 *  @param domain  主机地址
 *  @param success 成功
 *  @param failure 失败
 */
- (void)resloveDomain:(NSString *)domain
              success:(void(^)(NSDictionary *result))success
              failure:(void(^)(NSError *error))failure;
/**
 *  对指定ip测速
 *
 *  @param reslovedIP 测速ip
 *  @param success    成功
 *  @param failure    失败
 *  @discussion 成功result中包含ip和speed(KB/s)两个key
 */
- (void)detectSpeedWithReslovedIP:(NSString *)reslovedIP
                          success:(void(^)(NSDictionary *result))success
                          failure:(void(^)(NSError *error))failure;
@end

