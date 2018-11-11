 /*
     (c) 2016 Microchip Technology Inc. and its subsidiaries. You may use this
    software and any derivatives exclusively with Microchip products.

    THIS SOFTWARE IS SUPPLIED BY MICROCHIP "AS IS". NO WARRANTIES, WHETHER
    EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS SOFTWARE, INCLUDING ANY IMPLIED
    WARRANTIES OF NON-INFRINGEMENT, MERCHANTABILITY, AND FITNESS FOR A
    PARTICULAR PURPOSE, OR ITS INTERACTION WITH MICROCHIP PRODUCTS, COMBINATION
    WITH ANY OTHER PRODUCTS, OR USE IN ANY APPLICATION.

    IN NO EVENT WILL MICROCHIP BE LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE,
    INCIDENTAL OR CONSEQUENTIAL LOSS, DAMAGE, COST OR EXPENSE OF ANY KIND
    WHATSOEVER RELATED TO THE SOFTWARE, HOWEVER CAUSED, EVEN IF MICROCHIP HAS
    BEEN ADVISED OF THE POSSIBILITY OR THE DAMAGES ARE FORESEEABLE. TO THE
    FULLEST EXTENT ALLOWED BY LAW, MICROCHIP'S TOTAL LIABILITY ON ALL CLAIMS IN
    ANY WAY RELATED TO THIS SOFTWARE WILL NOT EXCEED THE AMOUNT OF FEES, IF ANY,
    THAT YOU HAVE PAID DIRECTLY TO MICROCHIP FOR THIS SOFTWARE.

    MICROCHIP PROVIDES THIS SOFTWARE CONDITIONALLY UPON YOUR ACCEPTANCE OF THESE
    TERMS.
 */

#include "oledC_shapeHandler.h"
#include <stdbool.h>
#include "oledC_shapes.h"

#define MAX_NUMBER_OF_SHAPES 32

void dummy(shape_t *shape){}

shape_t allParsedShapes[MAX_NUMBER_OF_SHAPES];
void initShapesMem(void){
    for(uint8_t i = 0; i < MAX_NUMBER_OF_SHAPES; i++){
        allParsedShapes[i].active = false;
        allParsedShapes[i].draw = dummy;
    }
}

void oledC_removeShape(uint8_t drawIndex){
    for(uint8_t i = drawIndex; i < (MAX_NUMBER_OF_SHAPES - 1); i++){
        allParsedShapes[i] = allParsedShapes[i+1];
    }
    allParsedShapes[MAX_NUMBER_OF_SHAPES-1].active = false;
}

shape_t* oledC_getShape(uint8_t index){
    index = index > MAX_NUMBER_OF_SHAPES ? MAX_NUMBER_OF_SHAPES : index;
    return &allParsedShapes[index];
}

void oledC_addShape(uint8_t drawIndex, enum OLEDC_SHAPE shape_type, shape_params_t *params){
    shape_t *newShape;
    drawIndex = drawIndex >= MAX_NUMBER_OF_SHAPES ? (MAX_NUMBER_OF_SHAPES-1) : drawIndex;
    for(uint8_t i = (MAX_NUMBER_OF_SHAPES-1); i > drawIndex && i > 0; i--){
        allParsedShapes[i] = allParsedShapes[i-1];
    }   
    
    newShape = &allParsedShapes[drawIndex];
    oledC_createShape(shape_type, params, newShape);
}
void oledC_redrawIndex(uint8_t indShape){
    allParsedShapes[indShape].draw(&allParsedShapes[indShape]);
}
void oledC_redrawTo(uint8_t endInd){
    oledC_redrawSome(0,endInd);
}
void oledC_redrawFrom(uint8_t startInd){
    oledC_redrawSome(startInd, MAX_NUMBER_OF_SHAPES);
}
void oledC_redrawSome(uint8_t startInd, uint8_t endInd){
    endInd = endInd > MAX_NUMBER_OF_SHAPES ? MAX_NUMBER_OF_SHAPES : endInd;
    for(uint8_t i = startInd; i < endInd; i++){
        if(allParsedShapes[i].active){
            allParsedShapes[i].draw(&allParsedShapes[i]);
        }
    }
}
void oledC_eraseShape(uint8_t indShape,uint16_t eraseColor){
    shape_t* ourShape = oledC_getShape(indShape);
    uint16_t saveColor = ourShape->params.point.color;
    ourShape->params.point.color = eraseColor;
    ourShape->draw(ourShape);
    ourShape->params.point.color = saveColor;
}
void oledC_eraseAll(uint16_t eraseColor){
    for(uint8_t i = 0; i < MAX_NUMBER_OF_SHAPES; i++){
        if(allParsedShapes[i].active){
            oledC_eraseShape(i,eraseColor);
        }
    }
}
void oledC_redrawAll(void){
    oledC_redrawSome(0,MAX_NUMBER_OF_SHAPES);
}
