//
//  QPUploadTaskManager.h
//  ALBBQuPaiPlugin
//
//  Created by zhangwx on 16/1/12.
//  Copyright © 2016年 Alipay. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "QPUploadTask.h"

@interface QPUploadTaskManager : NSObject

+ (instancetype)shared;

/** 创建上传任务
 * @param videoPath        视频文件路径
 * @param thumbnailPath    缩略图文件路径
 */
- (QPUploadTask *)createUploadTaskWithVideoPath:(NSString *)videoPath
                                  thumbnailPath:(NSString *)thumbnailPath;
/** 创建上传任务
 * @param videoPath        视频文件路径
 * @param thumbnailPath    缩略图文件路径
 * @param share            是否公开 0公开分享(default) 1私有 公开类视频不需要AccessToken授权
 * @param desc             description
 * @param tags             标签 多个标签用 "," 分隔符
 */
- (QPUploadTask *)createUploadTaskWithVideoPath:(NSString *)videoPath
                                  thumbnailPath:(NSString *)thumbnailPath
                                          share:(NSInteger)share
                                           desc:(NSString *)desc
                                           tags:(NSString *)tags;

// 开始任务
- (void)startUploadTask:(QPUploadTask *)uploadTask
               progress:(void(^)(CGFloat progress))progress
                success:(void(^)(QPUploadTask *uploadTask, NSString *remoteId))success
                failure:(void(^)(NSError *error))failure;
// 删除任务
- (void)removeUploadTask:(QPUploadTask *)uploadTask;
- (void)removeAllUploadTasks;
// 查询未完成任务
- (NSArray *)getAllUploadTasks;
@end
