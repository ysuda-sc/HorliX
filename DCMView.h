/*=========================================================================
  Program:   OsiriX

  Copyright (c) OsiriX Team
  All rights reserved.
  Distributed under GNU - GPL
  
  See http://www.osirix-viewer.com/copyright.html for details.

     This software is distributed WITHOUT ANY WARRANTY; without even
     the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
     PURPOSE.
=========================================================================*/




#import <Foundation/Foundation.h>
#import <Cocoa/Cocoa.h>

#include <OpenGL/gl.h>
#include <OpenGL/glext.h>
#include <OpenGL/glu.h>


#define STAT_UPDATE					0.6f
#define IMAGE_COUNT					1
#define IMAGE_DEPTH					32


// Tools.

enum
{
    tWL							=	0,
    tTranslate,					//	1
    tZoom,						//	2
    tRotate,					//	3
    tNext,						//	4
    tMesure,					//	5
    tROI,						//	6
	t3DRotate,					//	7
	tCross,						//	8
	tOval,						//	9
	tOPolygon,					//	10
	tCPolygon,					//	11
	tAngle ,					//	12
	tText,						//	13
	tArrow,						//	14
	tPencil,					//	15
	t3Dpoint,					//	16
	t3DCut,						//	17
	tCamera3D,					//	18
	t2DPoint,					//	19
	tPlain,						//	20
	tBonesRemoval,				//	21
	tWLBlended,					//  22
	tRepulsor,					//  23
	tLayerROI,					//	24
	tROISelector,				//	25
	tAxis,						//	26 //JJCP
	tDynAngle					//	27 //JJCP
};

extern NSString *pasteBoardOsiriX;
extern NSString *pasteBoardOsiriXPlugin;

enum { annotNone = 0, annotGraphics, annotBase, annotFull };
enum { barHide = 0, barOrigin, barFused, barBoth };
enum { syncroOFF = 0, syncroABS = 1, syncroREL = 2, syncroLOC = 3};

typedef enum {DCMViewTextAlignLeft, DCMViewTextAlignCenter, DCMViewTextAlignRight} DCMViewTextAlign;

@class DCMPix;
@class DCMView;
@class ROI;
@class OrthogonalMPRController;

@interface DCMView: NSOpenGLView
{
	int				_imageRows;
	int				_imageColumns;
	int				_tag;

	BOOL			flippedData;
	
	NSString		*yearOld;
	
	ROI				*curROI;
	BOOL			drawingROI, noScale, volumicSeries;
	DCMView			*blendingView;
	float			blendingFactor, blendingFactorStart;
	BOOL			eraserFlag; // use by the PaletteController to switch between the Brush and the Eraser
	BOOL			colorTransfer;
	unsigned char   *colorBuf, *blendingColorBuf;
	unsigned char   alphaTable[256], redTable[256], greenTable[256], blueTable[256];
	float			redFactor, greenFactor, blueFactor;
	long			blendingMode;
	float			sliceVector[ 3], slicePoint[ 3], slicePointO[ 3], slicePointI[ 3];
	float			sliceVector2[ 3], slicePoint2[ 3], slicePointO2[ 3], slicePointI2[ 3];
	float			slicePoint3D[ 3];
	float			syncRelativeDiff;
	long			syncSeriesIndex;
	
	float			mprVector[ 3], mprPoint[ 3];
	
	short			thickSlabMode, thickSlabStacks;
	
    NSImage         *myImage;
	
	NSMutableArray	*rectArray;
	
    NSMutableArray  *dcmPixList;
    NSArray			*dcmFilesList;
	NSMutableArray  *dcmRoiList, *curRoiList;
    DCMPix			*curDCM;
	
    NSTimer			*mouseModifiers;
	
    char            listType;
    
    short           curImage, startImage;
    
    short           currentTool, currentToolRight;
    
	BOOL			suppress_labels; // keep from drawing the labels when command+shift is pressed

    NSPoint         start, originStart, originOffsetStart, previous;
	
    float			startWW, curWW, startMin, startMax;
    float			startWL, curWL;

    float			bdstartWW, bdcurWW, bdstartMin, bdstartMax;
    float			bdstartWL, bdcurWL;
	
    NSSize          scaleStart, scaleInit;
    
    float           scaleValue, startScaleValue;
    float           rotation, rotationStart;
    NSPoint			origin, originOffset;
	NSPoint			cross, crossPrev;
	float			angle, slab, switchAngle;
	short			crossMove;
    
    NSMatrix        *matrix;
    
    long            count;
	
    BOOL            QuartzExtreme;
	
    BOOL            xFlipped, yFlipped;

	long			fontListGLSize[256];
	long			labelFontListGLSize[ 256];
	NSSize			stringSize;
	NSFont			*labelFont;
	NSFont			*fontGL;
	NSColor			*fontColor;
    GLuint          fontListGL;
	GLuint          labelFontListGL;
	float			fontRasterY;
	
    NSPoint         mesureA, mesureB;
    NSRect          roiRect;
	NSString		*stringID;
	NSSize			previousViewSize;

	float			contextualMenuInWindowPosX;
	float			contextualMenuInWindowPosY;	

	
	float			mouseXPos, mouseYPos;
	float			pixelMouseValue;
	long			pixelMouseValueR, pixelMouseValueG, pixelMouseValueB;
    
	float			blendingMouseXPos, blendingMouseYPos;
	float			blendingPixelMouseValue;
	long			blendingPixelMouseValueR, blendingPixelMouseValueG, blendingPixelMouseValueB;
	
    long			textureX, blendingTextureX;
    long			textureY, blendingTextureY;
    GLuint			* pTextureName;
	GLuint			* blendingTextureName;
    long			textureWidth, blendingTextureWidth;
    long			textureHeight, blendingTextureHeight;
    
	BOOL			f_ext_texture_rectangle; // is texture rectangle extension supported
	BOOL			f_arb_texture_rectangle; // is texture rectangle extension supported
	BOOL			f_ext_client_storage; // is client storage extension supported
	BOOL			f_ext_packed_pixel; // is packed pixel extension supported
	BOOL			f_ext_texture_edge_clamp; // is SGI texture edge clamp extension supported
	BOOL			f_gl_texture_edge_clamp; // is OpenGL texture edge clamp support (1.2+)
	unsigned long	edgeClampParam; // the param that is passed to the texturing parmeteres
	long			maxTextureSize; // the minimum max texture size across all GPUs
	long			maxNOPTDTextureSize; // the minimum max texture size across all GPUs that support non-power of two texture dimensions
	long			TEXTRECTMODE;
	
	BOOL			isKeyView; //needed for Image View subclass
	NSCursor		*cursor;
	BOOL			cursorSet;
	NSPoint			display2DPoint;
	
	NSMutableDictionary	*stringTextureCache;
	
	BOOL           _dragInProgress; // Are we drag and dropping
	NSTimer			*_mouseDownTimer; //Timer to check if mouseDown is Persisiting;
	NSTimer			*_rightMouseDownTimer; //Checking For Right hold
	NSImage			*destinationImage; //image will be dropping
	
	BOOL			_hasChanged, needToLoadTexture;
	
	//Context for rendering to iChat
	NSOpenGLContext *_alternateContext;
	NSDictionary *_hotKeyDictionary;
	
	BOOL			drawing;
	
	int				repulsorRadius;
	NSPoint			repulsorPosition;
	NSTimer			*repulsorColorTimer;
	float			repulsorAlpha, repulsorAlphaSign;
	BOOL			repulsorROIEdition;
	long            scrollMode;
	
	NSPoint			ROISelectorStartPoint, ROISelectorEndPoint;
	BOOL			selectorROIEdition;
	NSMutableArray	*ROISelectorSelectedROIList;
	
	BOOL			syncOnLocationImpossible, updateNotificationRunning;
	
	char			*resampledBaseAddr, *blendingResampledBaseAddr;
	char			*resampledTempAddr;
	BOOL			zoomIsSoftwareInterpolated;
	
	int				resampledBaseAddrSize, blendingResampledBaseAddrSize;
	
	NSLock			*drawLock;
	
	unsigned char*	iChatCursorTextureBuffer;
	GLuint			iChatCursorTextureName;
	NSSize			iChatCursorImageSize;
	NSPoint			iChatCursorHotSpot;
}
+ (void) setDefaults;
+ (void) setCLUTBARS:(int) c ANNOTATIONS:(int) a;
+ (void)setPluginOverridesMouse: (BOOL)override;
+ (void) computePETBlendingCLUT;
+ (NSString*) findWLWWPreset: (float) wl :(float) ww :(DCMPix*) pix;
+ (NSSize)sizeOfString:(NSString *)string forFont:(NSFont *)font;
+ (long) lengthOfString:( char *) cstr forFont:(long *)fontSizeArray;
+ (BOOL) intersectionBetweenTwoLinesA1:(NSPoint) a1 A2:(NSPoint) a2 B1:(NSPoint) b1 B2:(NSPoint) b2 result:(NSPoint*) r;
+ (float) Magnitude:( NSPoint) Point1 :(NSPoint) Point2;
- (BOOL) softwareInterpolation;
- (void) applyImageTransformation;
- (void) initFont;
- (NSMutableArray*) rectArray;
-(BOOL) flippedData;
- (void) gClickCountSetReset;
-(void) setFlippedData:(BOOL) f;
 -(NSMutableArray*) dcmPixList;
 -(NSMutableArray*) dcmRoiList;
 -(NSArray*) dcmFilesList;
- (long) indexForPix: (long) pixIndex; // Return the index into fileList that coresponds to the index in pixList
- (long) syncSeriesIndex;
- (void) setSyncSeriesIndex:(long) i;
- (float) syncRelativeDiff;
- (void) setSyncRelativeDiff: (float) v;
- (long) findPlaneAndPoint:(float*) pt :(float*) location;
- (unsigned char*) getRawPixels:(long*) width :(long*) height :(long*) spp :(long*) bpp :(BOOL) screenCapture :(BOOL) force8bits;
- (unsigned char*) getRawPixels:(long*) width :(long*) height :(long*) spp :(long*) bpp :(BOOL) screenCapture :(BOOL) force8bits :(BOOL) removeGraphical;
- (unsigned char*) getRawPixels:(long*) width :(long*) height :(long*) spp :(long*) bpp :(BOOL) screenCapture :(BOOL) force8bits :(BOOL) removeGraphical :(BOOL) squarePixels;
- (unsigned char*) getRawPixels:(long*) width :(long*) height :(long*) spp :(long*) bpp :(BOOL) screenCapture :(BOOL) force8bits :(BOOL) removeGraphical :(BOOL) squarePixels :(BOOL) allTiles;
- (unsigned char*) getRawPixelsView:(long*) width :(long*) height :(long*) spp :(long*) bpp :(BOOL) screenCapture :(BOOL) force8bits :(BOOL) removeGraphical :(BOOL) squarePixels;
- (void) setCrossPrev:(NSPoint) c;
-(NSPoint) cross;
-(NSPoint) crossPrev;
-(void) setSlab:(float) s;
-(void) blendingPropagate;
-(void) subtract:(DCMView*) bV;
-(void) multiply:(DCMView*) bV;
-(void) setBlendingMode:(long) f;
- (GLuint *) loadTextureIn:(GLuint *) texture blending:(BOOL) blending colorBuf: (unsigned char**) colorBufPtr textureX:(long*) tX textureY:(long*) tY redTable:(unsigned char*) rT greenTable:(unsigned char*) gT blueTable:(unsigned char*) bT textureWidth: (long*) tW textureHeight:(long*) tH resampledBaseAddr:(char**) rAddr resampledBaseAddrSize:(int*) rBAddrSize;
- (BOOL)xFlipped;
- (void)setXFlipped: (BOOL)v;
- (BOOL)yFlipped;
- (void)setYFlipped:(BOOL) v;
// checks to see if tool is for ROIs.  maybe better name - (BOOL)isToolforROIs:(long)tool
- (BOOL) roiTool:(long) tool;
- (void) sliderAction2DMPR:(id) sender;
- (void) setStringID:(NSString*) str;
- (NSString*) stringID;
- (float) angle;
- (void) prepareToRelease;
- (void) orientationCorrectedToView:(float*) correctedOrientation;
- (void) setCrossCoordinatesPer:(float) val;
- (void) setCrossCoordinates:(float) x :(float) y :(BOOL) update;
- (void) setCross:(long) x :(long)y :(BOOL) update;
- (void) setMPRAngle: (float) vectorMPR;
- (NSPoint) ConvertFromView2GL:(NSPoint) a;
- (NSPoint) ConvertFromGL2View:(NSPoint) a;
- (void) cross3D:(float*) x :(float*) y :(float*) z;
- (void) setWLWW:(float) wl :(float) ww;
- (void)discretelySetWLWW:(float)wl :(float)ww;
- (void) getWLWW:(float*) wl :(float*) ww;
- (void) getThickSlabThickness:(float*) thickness location:(float*) location;
- (void) setCLUT:( unsigned char*) r :(unsigned char*) g :(unsigned char*) b;
- (void) setCurrentTool:(short)i;
- (short) currentTool;
- (short) currentToolRight;
- (void) setRightTool:(short) i;
- (void) dealloc;
- (NSImage*) nsimage:(BOOL) originalSize;
- (NSImage*) nsimage:(BOOL) originalSize allViewers:(BOOL) allViewers;
- (void) setTheMatrix:(NSMatrix*)m;
- (void) setIndex:(short) index;
- (void) setIndexWithReset:(short) index :(BOOL)sizeToFit;
- (void) setDCM:(NSMutableArray*) c :(NSArray*)d :(NSMutableArray*)e :(short) firstImage :(char) type :(BOOL) reset;
- (short) curImage;
- (BOOL) suppressLabels;
- (void) sendSyncMessage:(short) inc;
- (void) setQuartzExtreme:(BOOL) set;
- (void) loadTextures;
- (void)loadTexturesCompute;
- (void) flipVertical:(id) sender;
- (void) flipHorizontal:(id) sender;
- (void) setFusion:(short) mode :(short) stacks;
- (void) FindMinimumOpenGLCapabilities;
- (float) scaleValue;
- (void) setScaleValue:(float) x;
- (float) rotation;
- (void) setRotation:(float) x;
- (NSPoint) rotatePoint:(NSPoint) a;
- (NSPoint) origin;
- (NSPoint) originOffset;
- (void) setOrigin:(NSPoint) x;
- (void) setOriginX:(float) x Y:(float) y;
- (void) setOriginOffset:(NSPoint) x;
- (void) setBlending:(DCMView*) bV;
- (double) pixelSpacing;
- (double) pixelSpacingX;
- (double) pixelSpacingY;
- (void) scaleToFit;
- (void) scaleBy2AndCenterShutter;
- (void) setBlendingFactor:(float) f;
- (void) sliderAction:(id) sender;
- (DCMPix*)curDCM;
- (void) roiSet;
- (void) roiSet:(ROI*) aRoi;
- (void) colorTables:(unsigned char **) a :(unsigned char **) r :(unsigned char **)g :(unsigned char **) b;
- (void) blendingColorTables:(unsigned char **) a :(unsigned char **) r :(unsigned char **)g :(unsigned char **) b;
- (void )changeFont:(id)sender;
- (void) getCrossCoordinates:(float*) x: (float*) y;
- (IBAction) sliderRGBFactor:(id) sender;
- (IBAction) alwaysSyncMenu:(id) sender;
- (void) getCLUT:( unsigned char**) r : (unsigned char**) g : (unsigned char**) b;
- (void) doSyncronize:(NSNotification*)note;
- (BOOL) volumicSeries;
- (id)initWithFrame:(NSRect)frame imageRows:(int)rows  imageColumns:(int)columns;
- (float)getSUV;
- (IBAction) roiLoadFromXMLFiles: (id) sender;
- (float)mouseXPos;
- (float)mouseYPos;
- (float) contextualMenuInWindowPosX;
- (float) contextualMenuInWindowPosY;
- (BOOL)checkHasChanged;
- (GLuint)fontListGL;
- (void) drawRectIn:(NSRect) size :(GLuint *) texture :(NSPoint) offset :(long) tX :(long) tY :(long) tW :(long) tH;
- (void) DrawNSStringGL: (NSString*) cstrOut :(GLuint) fontL :(long) x :(long) y;
- (void) DrawNSStringGL: (NSString*) str :(GLuint) fontL :(long) x :(long) y rightAlignment: (BOOL) right useStringTexture: (BOOL) stringTex;
- (void)DrawNSStringGL:(NSString*)str :(GLuint)fontL :(long)x :(long)y align:(DCMViewTextAlign)align useStringTexture:(BOOL)stringTex;
- (void) DrawCStringGL: ( char *) cstrOut :(GLuint) fontL :(long) x :(long) y;
- (void) DrawCStringGL: ( char *) cstrOut :(GLuint) fontL :(long) x :(long) y rightAlignment: (BOOL) right useStringTexture: (BOOL) stringTex;
- (void)DrawCStringGL:(char*)cstrOut :(GLuint)fontL :(long)x :(long)y align:(DCMViewTextAlign)align useStringTexture:(BOOL)stringTex;
- (void) drawTextualData:(NSRect) size :(long) annotations;
- (void) draw2DPointMarker;
- (void) setSyncro:(long) s;
- (void) drawImage:(NSImage *)image inBounds:(NSRect)rect;
- (long) syncro;
- (NSFont*)fontGL;
- (void) setScaleValueCentered:(float) x;
- (void) updateCurrentImage: (NSNotification*) note;
- (void) setImageParamatersFromView:(DCMView *)aView;
- (void) setRows:(int)rows columns:(int)columns;
- (void)setTag:( long)aTag;
- (long)tag;
- (void) updateTilingViews;
- (float)curWW;
- (float)curWL;
- (float)scaleValue;
- (NSPoint)origin;
- (int)rows;
- (int)columns;
- (DCMView *)blendingView;
- (float)blendingFactor;
- (float)blendingMode;
- (NSCursor *)cursor;
- (void) becomeMainWindow;
- (BOOL)eraserFlag;
- (void)setEraserFlag: (BOOL)aFlag;
- (NSManagedObject *)imageObj;
- (NSManagedObject *)seriesObj;
- (void) updatePresentationStateFromSeries;
- (void) updatePresentationStateFromSeriesOnlyImageLevel: (BOOL) onlyImage;
- (void) setCursorForView: (long) tool;
- (long) getTool: (NSEvent*) event;
- (void)resizeWindowToScale:(float)resizeScale;
- (float) getBlendedSUV;
- (OrthogonalMPRController*) controller;
- (void) roiChange:(NSNotification*)note;
- (void) roiSelected:(NSNotification*) note;
- (void) setStartWLWW;
- (void) stopROIEditing;
- (void) stopROIEditingForce:(BOOL) force;
- (void)subDrawRect: (NSRect)aRect;  // Subclassable, default does nothing.
- (void) setDrawing:(BOOL) v;
- (void) updateImage;
- (BOOL) shouldPropagate;

// methodes to access global variables (for plugins)
+ (BOOL) display2DMPRLines;
+ (unsigned char*) PETredTable;
+ (unsigned char*) PETgreenTable;
+ (unsigned char*) PETblueTable;

//Timer method to start drag
- (void) startDrag:(NSTimer*)theTimer;
- (void)deleteMouseDownTimer;
- (id)dicomImage;

//windowController
- (id)windowController;
- (BOOL)is2DViewer;

//Hot key action
-(BOOL)actionForHotKey:(NSString *)hotKey;

//iChat
// New Draw method to allow for IChat Theater
- (void) drawRect:(NSRect)aRect withContext:(NSOpenGLContext *)ctx;
- (BOOL)_checkHasChanged:(BOOL)flag;

// Methods for mouse drag response  Can be modified for subclassing
// This allow the various tools to  have different responses indifferent subclasses.
// Making it easie to modify mouseDragged:
- (NSPoint)currentPointInView:(NSEvent *)event;
- (BOOL)checkROIsForHitAtPoint:(NSPoint)point forEvent:(NSEvent *)event;
- (void)mouseDraggedForROIs:(NSEvent *)event;
- (void)mouseDraggedCrosshair:(NSEvent *)event;
- (void)mouseDragged3DRotate:(NSEvent *)event;
- (void)mouseDraggedZoom:(NSEvent *)event;
- (void)mouseDraggedTranslate:(NSEvent *)event;
- (void)mouseDraggedRotate:(NSEvent *)event;
- (void)mouseDraggedImageScroll:(NSEvent *)event;
- (void)mouseDraggedBlending:(NSEvent *)event;
- (void)mouseDraggedWindowLevel:(NSEvent *)event;
- (void)mouseDraggedRepulsor:(NSEvent *)event;
- (void)mouseDraggedROISelector:(NSEvent *)event;

- (void)deleteROIGroupID:(NSTimeInterval)groupID;

@end
