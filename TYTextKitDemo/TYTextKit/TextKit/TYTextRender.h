//
//  TYTextRender.h
//  TYTextKitDemo
//
//  Created by tany on 2017/9/26.
//  Copyright © 2017年 tany. All rights reserved.
//

#import <UIKit/UIKit.h>
#import "NSAttributedString+TYTextKit.h"
#import "TYTextStorage.h"
#import "TYTextAttachment.h"
#import "TYTextAttribute.h"
#import "TYLayoutManager.h"

NS_ASSUME_NONNULL_BEGIN
@interface TYTextRender : NSObject

@property (nonatomic, strong, nullable) NSTextStorage *textStorage;
@property (nonatomic, strong, readonly) NSLayoutManager *layoutManager;
@property (nonatomic, strong, readonly) NSTextContainer *textContainer;

// textStorage will be edited, use in textView
@property (nonatomic, assign) BOOL editable;

/**
 text is inset within line fragment rectangles.default 0
 */
@property (nonatomic, assign) CGFloat lineFragmentPadding;
@property (nonatomic, assign) NSLineBreakMode lineBreakMode;
@property (nonatomic, assign) NSUInteger maximumNumberOfLines;

/**
 render size
 */
@property (nonatomic, assign) CGSize size;

/**
 text highlight background corner radius. default 4.0
 @discussion only support TYLayoutManager
 */
@property (nonatomic, assign) CGFloat highlightBackgroudRadius;

/**
 default YES, if NO every time call textStorage'attachViews will re-get attachViews.
 */
@property (nonatomic, assign) BOOL onlySetTextStorageWillGetAttachViews;

/**
 text attributed contain attachment views or layers
 */
@property (nonatomic, strong, readonly, nullable) NSArray<TYTextAttachment *> *attachmentViews;
@property (nonatomic, strong, readonly, nullable) NSSet<TYTextAttachment *> *attachmentViewSet;

/**
 default NO,if YES, only set render size will caculate text bounds and cache
 @discussion if YES cache text bounds will optimize performance,otherwise every time you call -(CGRect)textBound will re-caculate text bound.
 */
@property (nonatomic, assign) BOOL onlySetRenderSizeWillGetTextBounds;

/**
 visible text bound
 @discussion render should set size before call this, you can set onlySetRenderSizeWillGetTextBounds YES,will cahce text bounds
 */
@property (nonatomic, assign, readonly) CGRect textBound;

// initialize
- (instancetype)initWithAttributedText:(NSAttributedString *)attributedText;
- (instancetype)initWithTextStorage:(NSTextStorage *)textStorage;
- (instancetype)initWithTextContainer:(NSTextContainer *)textContainer;

/**
 return text max size if maximumNumberOfLines 0,oherwise maximumNumberOfLines text size
 @param renderWidth text render width
 */
- (CGSize)textSizeWithRenderWidth:(CGFloat)renderWidth;

/**
 visible text range,must have been set render size
 */
- (NSRange)visibleCharacterRange;

/**
 text bound for character range,must have been set render size
 */
- (CGRect)boundingRectForCharacterRange:(NSRange)characterRange;

/**
 text character index at piont
 */
- (NSInteger)characterIndexForPoint:(CGPoint)point;

/**
 draw text at point
 */
- (void)drawTextAtPoint:(CGPoint)point;

@end


@interface TYTextRender (Rendering)

/**
 text rect on render
 @discussion when text rendered display,will have value
 */
@property (nonatomic, assign, readonly) CGRect textRectOnRender;

/**
 visible text range on render
 @discussion when text rendered display,will have value
 */
@property (nonatomic, assign, readonly) NSRange visibleCharacterRangeOnRender;

/**
 set text highlight
 */
- (void)setTextHighlight:(TYTextHighlight *)textHighlight range:(NSRange)range;

- (void)drawTextAtPoint:(CGPoint)point isCanceled:(BOOL (^__nullable)(void))isCanceled;

@end

NS_ASSUME_NONNULL_END
