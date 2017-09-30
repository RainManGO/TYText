//
//  TYTextAttachment.m
//  TYTextKitDemo
//
//  Created by tany on 2017/9/26.
//  Copyright © 2017年 tany. All rights reserved.
//

#import "TYTextAttachment.h"
#import "NSAttributedString+TYTextKit.h"
#import <pthread.h>

#define TYAssertMainThread() NSAssert(0 != pthread_main_np(), @"This method must be called on the main thread!")

@interface TYTextAttachment ()
@property (nonatomic, assign) NSRange range;
@end

@implementation TYTextAttachment
@dynamic image;

- (void)setSize:(CGSize)size {
    _size = size;
    self.bounds = CGRectMake(0, 0, _size.width, _size.height);
}

- (void)setBounds:(CGRect)bounds {
    [super setBounds:bounds];
    _size = bounds.size;
}

- (void)setBaseline:(CGFloat)baseline {
    _baseline = baseline;
    self.bounds = CGRectOffset(self.bounds, 0, baseline);
}

#pragma mark - public

- (void)setFrame:(CGRect)frame {
    _view.frame = frame;
    _layer.frame = frame;
}

- (void)addToSuperView:(UIView *)superView {
    TYAssertMainThread();
    if (_view) {
        [superView addSubview:_view];
    }else if (_layer) {
        [superView.layer addSublayer:_layer];
    }
}

- (void)removeFromSuperView {
    TYAssertMainThread();
    [_view removeFromSuperview];
    [_layer removeFromSuperlayer];
}

#pragma mark - NSTextAttachmentContainer

- (nullable UIImage *)imageForBounds:(CGRect)imageBounds textContainer:(nullable NSTextContainer *)textContainer characterIndex:(NSUInteger)charIndex {
    _position = CGPointMake(imageBounds.origin.x, imageBounds.origin.y - _size.height);
    return self.image;
}

- (CGRect)attachmentBoundsForTextContainer:(NSTextContainer *)textContainer proposedLineFragment:(CGRect)lineFrag glyphPosition:(CGPoint)position characterIndex:(NSUInteger)charIndex {
    if (_verticalAlignment == TYAttachmentAlignmentBaseline || self.bounds.origin.y > 0) {
        return self.bounds;
    }
    CGFloat offset = 0;
    UIFont *font = [textContainer.layoutManager.textStorage ty_fontAtIndex:charIndex effectiveRange:nil];
    switch (_verticalAlignment) {
        case TYAttachmentAlignmentCenter:
            offset = (_size.height-font.capHeight)/2;
            break;
        case TYAttachmentAlignmentBottom:
            offset = _size.height-font.capHeight;
        default:
            break;
    }
    return CGRectMake(0, -offset, _size.width, _size.height);
}

@end

@implementation NSAttributedString (TYTextAttachment)

- (NSArray *)attachViews {
    NSMutableArray *array = [NSMutableArray array];
    [self enumerateAttribute:NSAttachmentAttributeName inRange:NSMakeRange(0, self.length) options:kNilOptions usingBlock:^(TYTextAttachment *value, NSRange subRange, BOOL *stop) {
        if ([value isKindOfClass:[TYTextAttachment class]] && (value.view || value.layer)) {
            ((TYTextAttachment *)value).range = subRange;
            [array addObject:value];
        }
    }];
    return array.count > 0 ? [array copy] : nil;
}

@end