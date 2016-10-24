//
//  QPUploadTask.h
//  ALBBQuPaiPlugin
//
//  Created by zhangwx on 16/1/12.
//  Copyright © 2016年 Alipay. All rights reserved.
//

#import <Foundation/Foundation.h>

#import "QPJSONModel.h"

@interface QPUploadTask : QPJSONModel
@property (nonatomic, copy) NSString *taskId;
@property (nonatomic, copy) NSString *uploadId;
@property (nonatomic, copy) NSString *videoPath;
@property (nonatomic, copy) NSString *thumbnailPath;
@property (nonatomic, copy) NSString *videoMD5;
@property (nonatomic, copy) NSString *range;
@property (nonatomic, assign) NSInteger videoLength;
@property (nonatomic, assign) NSInteger thumbnailLength;
@property (nonatomic, copy) NSString *tags;
@property (nonatomic, copy) NSString *desc;
@property (nonatomic, assign) NSInteger share;

@property (nonatomic, assign) BOOL uploadFinished;
@property (nonatomic, copy) NSString *remoteId;

- (CGFloat)progress;
@end
