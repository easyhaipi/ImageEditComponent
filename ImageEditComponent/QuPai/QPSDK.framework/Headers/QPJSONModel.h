//
//  JSONModel.h
//  QupaiSDK
//
//  Created by yly on 15/6/26.
//  Copyright (c) 2015年 lyle. All rights reserved.
//

#import <Foundation/Foundation.h>

@protocol Ignore
@end

@protocol Optional
@end


@interface QPJSONModel : NSObject

- (instancetype)initWithString:(NSString*)string error:(NSError**)err;
- (instancetype)initWithDictionary:(NSDictionary *)dic;
- (instancetype)initWithFile:(NSString *)path;

- (NSDictionary *)toDictionary;
- (void)jsonToFile:(NSString *)path;

@end
