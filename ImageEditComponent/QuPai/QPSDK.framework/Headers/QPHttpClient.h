//
//  QPHttpClient.h
//  ALBBQuPaiPlugin
//
//  Created by zhangwx on 15/12/31.
//  Copyright © 2015年 Alipay. All rights reserved.
//

#import <Foundation/Foundation.h>

@interface QPHttpClient : NSObject

@property (nonatomic, strong) NSURL *url;
@property (nonatomic, strong) NSDictionary *params;

+ (instancetype)clientWithURL:(NSURL *)url params:(NSDictionary *)params;

- (void)appendPartWithFileURL:(NSURL *)fileUrl
                         name:(NSString *)name;
- (void)appendPartWithFileData:(NSData *)data
                          name:(NSString *)name
                      fileName:(NSString *)fileName
                      mimeType:(NSString *)mimeType;


-(void)postWithCompletionHandler:(void (^)(NSURLResponse* response, NSData* data, NSError* connectionError)) handler;

@end
