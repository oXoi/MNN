//
//  CommonOptFunction.h
//  MNN
//
//  Created by MNN on 2018/07/16.
//  Copyright © 2018, Alibaba Group Holding Limited
//

#ifndef CommonOptFunction_h
#define CommonOptFunction_h

#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <vector>

#include <MNN/Rect.h>
#include "core/Macro.h"
#include "backend/cpu/compute/Int8FunctionsOpt.h"

extern "C" {
#ifdef __aarch64__
#ifdef MNN_LOW_MEMORY
void MNNGeneralIm2col_Fp32Arm82(float* destOrigin, float const** sourceGroup, const int32_t* info, const int32_t* el, int32_t LP, int32_t pack);
void MNNGeneralIm2col_Fp32Arm86(float* destOrigin, float const** sourceGroup, const int32_t* info, const int32_t* el, int32_t LP, int32_t pack);
void MNNGeneralIm2col_Fp32Sme2(float* destOrigin, float const** sourceGroup, const int32_t* info, const int32_t* el, int32_t LP, int32_t pack);
void MNNLocalMinMaxFP32_Pack4(float* dstMin, float* dstMax, const float* source, size_t blockNum, size_t blockLU, size_t EP, size_t LP, size_t loadDstBuffer);
void MNNLocalMinMaxFP32_Pack8(float* dstMin, float* dstMax, const float* source, size_t blockNum, size_t blockLU, size_t EP, size_t LP, size_t loadDstBuffer);
void MNNDynamicQuantFP32_Pack4(const float* src, int8_t* dst, const float* scale, size_t src_depth_quad, size_t realSize, const float* bias, size_t pack);
void MNNDynamicQuantFP32_Pack8(const float* src, int8_t* dst, const float* scale, size_t src_depth_quad, size_t realSize, const float* bias, size_t pack);
void MNNAbsMaxFP32_Pack4(const float* source, float* absmax, size_t src_depth_quad, size_t realSize, int pack);
void MNNAbsMaxFP32_Pack8(const float* source, float* absmax, size_t src_depth_quad, size_t realSize, int pack);
void MNNQuantScaleFP32(float* absmax, float* quant_scale, float* dequant_scale, size_t thread, size_t batch);
void MNNDynamicUpdateConvBiasScale(float* newbias, float* oldbias, float* weightKernelSum, float* inputZero, size_t ocQuad);
#endif
#ifdef MNN_SME2
void MNNPackedMatMulRemainFP32_SME2(float* C, const float* A, const float* B, size_t eSize, const size_t* parameter, const float* postParameters, const float* bias, const float* k, const float* b);

#endif
#endif
void MNNFp32ToFp8(uint8_t* dst, const float* src, size_t size);
void MNNFp8ToFp32(float* dst, const uint8_t* src, size_t size);
void MNNFp16ToFp8(uint8_t* dst, const uint16_t* src, size_t size);
void MNNFp8ToFp16(uint16_t* dst, const uint8_t* src, size_t size);

void MNNReluWithSlope(float* dst, const float* src, size_t sizeQuad, float slope);

void MNNReluInt8(int8_t* dst, const int8_t* src, size_t size, ssize_t zeroPoint);

void MNNReluWithSlopeChannel(float* dst, const float* src, const float* slope, size_t sizeQuad, size_t depthQuad);

void MNNHardSwish(float* dst, const float* src, size_t size);

void MNNGelu(float* dst, const float* src, size_t size, float* parameters);

void MNNPackC4(float* dst, const float* src, size_t area, size_t depth, int* areaOffset);
void MNNPackC4Origin(float* dst, const float* src, size_t area, size_t depth, int areaOffset);

void MNNPackC2(double* dst, const double* src, size_t area, size_t depth, int* areaOffset);
void MNNPackC2Origin(double* dst, const double* src, size_t area, size_t depth, int areaOffset);
void MNNPackInt8C2(float* dst, const float* src, size_t area, size_t depth, int* areaOffset);
void MNNPackInt8C2Origin(float* dst, const float* src, size_t area, size_t depth, int areaOffset);

void MNNPackC4Int16(int16_t* dst, const int16_t* src, size_t area,size_t depth, int* areaOffset);

void MNNPackC4Uint8(uint8_t* dst, const uint8_t* src, size_t area,size_t depth, int* areaOffset);

void MNNUnpackC4(float* dst, const float* src, size_t area, size_t depth, int* areaOffset);
void MNNUnpackC4Origin(float* dst, const float* src, size_t area, size_t depth, int areaOffset);

void MNNUnpackC2(double* dst, const double* src, size_t area, size_t depth, int* areaOffset);
void MNNUnpackC2Origin(double* dst, const double* src, size_t area, size_t depth, int areaOffset);
void MNNUnpackC2Float(float* dst, const float* src, size_t area, size_t depth, int* areaOffset, int pack = 1);

void MNNUnpackInt8C2(float* dst, const float* src, size_t area, size_t depth, int* areaOffset);
void MNNUnpackInt8C2Origin(float* dst, const float* src, size_t area, size_t depth, int areaOffset);

void MNNUnpackC4Int16(int16_t* dst, const int16_t* src, size_t area,size_t depth, int* areaOffset);

void MNNUnpackC4Uint8(uint8_t* dst, const uint8_t* src, size_t area,size_t depth, int* areaOffset);

void MNNScaleAndAddBias(float* dst, const float* src, const float* bias, const float* alpha, size_t planeNumber,
                        size_t biasNumber);
void MNNScaleAndAddBiasScalar(float* dst, const float* src, float bias, float alpha, size_t number);

// TODO: Swap the name for MNNUnpackTranspose and MNNPackTranspose
void MNNUnpackTranspose(float* dst, const float* src, size_t area, size_t depth, int* areaOffset);
void MNNUnpackTransposeInt16(int16_t* dst, const int16_t* src, size_t area,size_t depth, int* areaOffset);
void MNNUnpackTransposeUint8(uint8_t* dst, const uint8_t* src, size_t area,size_t depth, int* areaOffset);

void MNNPackTranspose(float* dst, const float* src, size_t area, size_t depth, int* areaOffset);
void MNNPackTransposeInt16(int16_t* dst, const int16_t* src, size_t area,size_t depth, int* areaOffset);
void MNNPackTransposeUint8(uint8_t* dst, const uint8_t* src, size_t area,size_t depth, int* areaOffset);

void MNNCopyC4WithStride(const float* source, float* dest, size_t srcStride, size_t dstStride, size_t count);
void MNNAddC4WithStride(const float* source, float* dest, size_t srcStride, size_t dstStride, size_t count);

void MNNUInt8ToInt16WithOffsetC4Common(int16_t* dst, const uint8_t* src, size_t zeroPoint, size_t sizeQuad,
                                       size_t dstStride, size_t srcStride);
void MNNUInt8ToInt16WithOffsetC4Fast(int16_t* dst, const uint8_t* src, size_t zeroPoint, size_t sizeQuad,
                                     size_t depthQuad, size_t dstZStep, size_t srcZStep);
void MNNMaxFloat(float* input, float* maxBuffer, int32_t inputCountUnit);
void MNNMinFloat(float* input, float* maxBuffer, int32_t inputCountUnit);
void MNNPowC8(float* dest, const float* source, const float* powfParam, size_t betaInt, size_t countC8);

void MNNExpC8(float* dest, const float* source, float* offset, const float* parameters, size_t countC8);

// Offset: o0, o1, o2, o3: dst = exp(src*o0+o2)+o1, o3 = o3+sum(dst)
void MNNExp(float* dst, const float* src, float* offset, size_t dataSize);
void MNNSin(float* dst, const float* src, size_t dataSize);
void MNNTanh(float* dst, const float* src, size_t dataSize);
void MNNSigmoid(float* dst, const float* src, size_t dataSize);
void MNNSigmoidLowp(float* dst, const float* src, size_t dataSize);
void MNNSiLu(float* dst, const float* src, size_t dataSize);
void MNNSiLuLowp(float* dst, const float* src, size_t dataSize);
void MNNReluWithSlopeCommon(float* dst, const float* src, size_t size, float slope);
void MNNHardSwishCommon(float* dst, const float* src, size_t size);
void MNNGeluCommon(float* dst, const float* src, size_t size);
void MNNGeluStandardCommon(float* dst, const float* src, size_t size);
void MNNSoftmax(float* dest, const float* source, size_t size);
void MNNNorm(float* dest, const float* source, const float *gamma, const float *beta, float epsilon, size_t size, bool RMSNorm = false);

// Get Pack for MatMul's e , l , h , the pack number must be 1 or 4 * n
void MNNGetMatMulPackMode(int* eP, int *lP, int* hP);

void MNNGetSparseMatMulPackMode(int* eP, int *lP, int* hP);

/**
 int number = info[0];
 int eSrcStride = info[1];
 int eDstStride = info[2];
 int xStride = info[3];

el: number * 4
 0: e
 1: l
 2: e-offset
 3: l-offset
 */
void MNNPackC4ForMatMul_A(float* destOrigin, float const** sourceGroup, const int32_t* info, const int32_t* el);

void MNNPackForMatMul_B(float* dest, const float* source, size_t h, size_t kernelsize, size_t ic, bool transpose);

// parameters: e, l, h, CStride, AStride, BStride
void MNNPackedMatMul(float* C, const float* A, const float* B, const size_t* parameter, const float* postParameters, const float* bias, const float* k, const float* b);
void MNNFunctionInit();
void MNNPackedMatMulRemain(float* C, const float* A, const float* B, size_t eSize, const size_t* parameter, const float* postParameters, const float* bias, const float* k, const float* b);
void MNNPackedMatMul_int4(float* C, const float* A, const float* B, const size_t* parameter, const float* postParameters, const float* bias, const float* k, const float* b);
void MNNPackedMatMulRemain_int4(float* C, const float* A, const float* B, size_t eSize, const size_t* parameter, const float* postParameters, const float* bias, const float* k, const float* b);
void MNNPackedMatMul_int8(float* C, const float* A, const float* B, const size_t* parameter, const float* postParameters, const float* bias, const float* k, const float* b);
void MNNPackedMatMulRemain_int8(float* C, const float* A, const float* B, size_t eSize, const size_t* parameter, const float* postParameters, const float* bias, const float* k, const float* b);

void MNNPackForSparseMatMul_B(float* dest, unsigned int* NNZMap, int* dataOffsetMap, int sparseBlockOC, const float* source, size_t h, size_t l, const int eP, bool transpose);
struct SparseMatMulParas
{
    float* C;
    const float* A;
    const float* B;
    unsigned int* NNZMap;
    int* dataOffsetMap;
};
void MNNPackedSparseMatMulEpx1(float* C, const float* A, const float* B, size_t eSize, const size_t* parameter, const float* postParameters, const float* bias, unsigned int* NNZMap, int* dataOffsetMap);

void MNNPackedSparseMatMulEpx4(float* C, const float* A, const float* B, size_t eSize, const size_t* parameter, const float* postParameters, const float* bias, unsigned int* NNZMap, int* dataOffsetMap);


int MNNGetC4DivNumber(int hP);

void MNNAxByClampBroadcastUnit(float* C, const float* A, const float* B, size_t width, size_t cStride, size_t aStride, size_t height, const float* parameters);

// dim: 4-element, sizeDW, sizeDH, strideSW, strideDH
void MNNTranspose32Bit(int32_t* dstO, const int32_t* srcO, int32_t* dim); // not C4
void MNNTranspose16Bit(int16_t* dstO, const int16_t* srcO, int32_t* dim); // not C4

void MNNVectorTop1Float(float* input, float* maxValue, int32_t* maxIndex, size_t inputCountUnit);
void MNNVectorTop1Int32(int32_t* input, int32_t* maxValue, int32_t* maxIndex, size_t inputCountUnit);
struct MatMulParam {
    int32_t e;
    int32_t l;
    int32_t h;
    int32_t numberThread;
    bool ATranspose;
    bool BTranspose;
};
void MNNComputeMatMulForE_1(const float* A, const float* B, float* C, const float* biasPtr, const MatMulParam* param, size_t tId);

void MNNCopyC4Int16WithStride(const float* sourceF, float* destF, size_t srcStride, size_t dstStride, size_t count);
void MNNInt8ToInt16(int16_t* dest, const int8_t* source, size_t count);

struct SumByAxisParams {
    ssize_t kernelCountUnitDouble;
    ssize_t unitColBufferSize;
    ssize_t DST_XUNIT;
    ssize_t SRC_UNIT;
    ssize_t blockNum;
    ssize_t oneScale;
    ssize_t valid;
    ssize_t kernelxy;
    ssize_t LU;
    ssize_t inputBlock;
};
#ifdef __aarch64__
void MNNPermuteSumWeightInt4Arm86(uint8_t* dest, uint8_t* source, size_t outside, size_t inside, float* kernlesum);
void MNNPermuteSumWeightInt4Arm82(uint8_t* dest, uint8_t* source, size_t outside, size_t inside, float* kernlesum);
void MNNPermuteSumWeightInt4Sme2(uint8_t* dest, uint8_t* source, size_t outside, size_t inside, float* kernlesum);
void MNNSumWeightInt8Arm86(float* kernelsum, int8_t* source, size_t outside, size_t reduceAxis, size_t hP, size_t lP);
void MNNSumWeightInt8Arm82(float* kernelsum, int8_t* source, size_t outside, size_t reduceAxis, size_t hP, size_t lP);
void MNNSumWeightInt8Sme2(float* kernelsum, int8_t* source, size_t outside, size_t reduceAxis, size_t hP, size_t lP);
#endif
}

typedef void(*MNNBinaryExecute)(void* outputRaw, const void* inputRaw0, const void* inputRaw1, int elementSize, int broadcastIndex);
typedef void(*MNNUnaryExecute)(void* outputRaw, const void* inputRaw, int elementSize);
typedef void(*MNNUnaryExecuteInt8)(void* outputRaw, const void* inputRaw, int elementSize, QuanPrePostParameters* params);
typedef void(*MNNCopyWithStride)(uint8_t* dstO, const uint8_t* srcO, int size, int stride, int ds);
typedef void(*MNNBinaryExecInt8)(int8_t* outputRaw, const int8_t* inputRaw0, const int8_t* inputRaw1, ssize_t* inputScalesInt32, float* inputScalesFp32, const QuanPrePostParameters* params, size_t elementSize, size_t needBroadcast);

constexpr int InputTileMax = 14; // same value from DynamicGemm.h, cannot include from different backend code.

namespace MNN {
struct MatmulRelatedFunctions {
    // coreFunctions
    void (*MNNSumWeightInt8)(float* kernelsum, int8_t* source, size_t outside, size_t reduceAxis, size_t hP, size_t lP) = nullptr;
    void (*MNNReorderWeightInt4)(uint8_t* dest, const uint8_t* source, int32_t* shape, size_t size, float* kernelsum) = nullptr;
    void (*MNNPackedMatMul)(float* C, const float* A, const float* B, const size_t* parameter, const float* postParameters, const float* bias, const float* k, const float* b) = nullptr;
    void (*MNNPackedMatMulRemain)(float* C, const float* A, const float* B, size_t eSize, const size_t* parameter, const float* postParameters, const float* bias, const float* k, const float* b) = nullptr;
    void (*MNNGetMatMulPackMode)(int* eP, int* lP, int* hP) = nullptr;
    void (*MNNPackC4ForMatMul_A)(float* destOrigin, float const** sourceGroup, const int32_t* info, const int32_t* el) = nullptr;
    void (*MNNPackForMatMul_B)(float* dest, const float* source, size_t h, size_t kernelsize, size_t ic, bool transpose) = nullptr;
    void(*MNNGeneralIm2Col)(float* destOrigin, float const** sourceGroup, const int32_t* info, const int32_t* el, int32_t LP, int32_t pack) = nullptr;

    // int8CoreFunctions
    void(*Int8GemmKernel)(int8_t* dst, const int8_t* src, const int8_t* weight, size_t src_depth_quad, size_t dst_step, size_t dst_depth_quad, const QuanPostTreatParameters* post, size_t realCount) = nullptr;
    void(*Int8GemmKernelFast)(int8_t* dst, const int8_t* src, const int8_t* weight, size_t src_depth_quad, size_t dst_step, size_t dst_depth_quad, const QuanPostTreatParameters* post, size_t realCount) = nullptr;
    void(*MNNGetGemmUnit)(int* UNIT, int* SRC_UNIT, int* DST_XUNIT) = nullptr;
    void(*MNNPackC4Int8ForMatMul_A)(int8_t* destOrigin, int8_t const** sourceGroup, const int32_t* info, const int32_t* el) = nullptr;
    void(*MNNGemmInt8AddBiasScale_Unit_FP16)(int8_t* dst, const int8_t* src, const int8_t* weight, size_t src_depth_quad, size_t dst_step, size_t dst_depth_quad, const QuanPostTreatParameters* post, size_t realDstCount) = nullptr;
    void(*MNNGemmInt8AddBiasScale_w4_Unit_FP16)(int8_t* dst, const int8_t* src, const int8_t* weight, size_t src_depth_quad, size_t dst_step, size_t dst_depth_quad, const QuanPostTreatParameters* post, size_t realDstCount) = nullptr;
    void(*Int8GemmKernel_W4)(int8_t* dst, const int8_t* src, const int8_t* weight, size_t src_depth_quad, size_t dst_step, size_t dst_depth_quad, const QuanPostTreatParameters* post, size_t realDstCount) = nullptr;
    void(*MNNSumByAxisLForMatmul_A)(float* dest, int8_t* source, const float* dequantScale, ssize_t realDstCount, SumByAxisParams sumParams) = nullptr;
};

struct CoreFunctions {
    // fp8
    void (*MNNFp32ToFp8)(uint8_t* dst, const float* src, size_t size);
    void (*MNNFp16ToFp8)(uint8_t* dst, const uint16_t* src, size_t size);
    void (*MNNFp8ToFp32)(float* dst, const uint8_t* src, size_t size);
    void (*MNNFp8ToFp16)(uint16_t* dst, const uint8_t* src, size_t size);

    // cpu feature
    bool supportFp16arith = false;
    bool supportSDot = false;
    bool supportI8mm = false;
    bool supportSME2 = false;
    /**MatMul Pack and Functions*/
    void(*MNNGetMatMulPackMode)(int* eP, int *lP, int* hP);
    void(*MNNGetSparseMatMulPackMode)(int* eP, int *lP, int* hP);
    void(*MNNPackC4ForMatMul_A)(float* destOrigin, float const** sourceGroup, const int32_t* info, const int32_t* el);
    void(*MNNPackForMatMul_B)(float* dest, const float* source, size_t h, size_t kernelsize, size_t ic, bool transpose);
    void(*MNNGeneralIm2Col)(float* destOrigin, float const** sourceGroup, const int32_t* info, const int32_t* el, int32_t LP, int32_t pack);
    // parameters: e, l, h, CStride, AStride, BStride
    void(*MNNPackedMatMul)(float* C, const float* A, const float* B, const size_t* parameter, const float* postParameters, const float* bias, const float* k, const float* b);
    void(*MNNPackedMatMulRemain)(float* C, const float* A, const float* B, size_t eSize, const size_t* parameter, const float* postParameters, const float* bias, const float* k, const float* b);
    void(*MNNAbsMax)(const float* source, float* absmax, size_t src_depth_quad, size_t realSize, int pack) = nullptr;
    void(*MNNQuantScale)(float* absmax, float* quant_scale, float* dequant_scale, size_t thread, size_t batch) = nullptr;
    void(*MNNDynamicQuant)(const float* src, int8_t* dst, const float* scale, size_t src_depth_quad, size_t realSize, int pack, const float* bias) = nullptr;
    void(*MNNPackedMatMul_int8)(float* C, const float* A, const float* B, const size_t* parameter, const float* postParameters, const float* bias, const float* k, const float* b) = nullptr;
    void(*MNNPackedMatMulRemain_int8)(float* C, const float* A, const float* B, size_t eSize, const size_t* parameter, const float* postParameters, const float* bias, const float* k, const float* b) = nullptr;
    void(*MNNComputeMatMulForH_1)(const float* A, const float* B, float* C, const float* biasPtr, const MatMulParam* param, size_t tId);
    void(*MNNComputeMatMulForE_1)(const float* A, const float* B, float* C, const float* biasPtr, const MatMulParam* param, size_t tId);
    void(*MNNCountMaxMinValue)(const float* source, float* minVal, float* maxVal, size_t size);
    void(*MNNDynamicUpdateConvBiasScale)(float* newbias, float* oldbias, float* weightKernelSum, float* inputZero, size_t ocQuad);
    void(*MNNAsyQuantInfo)(float* scale, float* bias, float* qscale, float* qbias, float* dstMin, float* dstMax, const float* src, const size_t* info);
    void(*MNNAsyQuantFunc)(int8_t* dst, const float* src, float* qscale, float* qbias, const size_t* info);
    typedef void(*MNNPackedMatMulKernel)(float* C, const float* A, const float* B, const size_t* parameter, const float* postParameters, const float* bias);

    MNNPackedMatMulKernel MNNPackedMatMulOC16Functions[InputTileMax] = {0};
    MNNPackedMatMulKernel MNNPackedMatMulOC32Functions[InputTileMax] = {0};
    MNNPackedMatMulKernel MNNPackedMatMulOC48Functions[InputTileMax] = {0};

    // For Atomic Op
    MNNBinaryExecute(*MNNSelectBinaryFunctionForFloat)(int opType);
    MNNUnaryExecute(*MNNSelectUnaryFunctionForFloat)(int opType, int precisionMode);
#ifdef MNN_SUPPORT_QUANT_EXTEND
    MNNUnaryExecuteInt8(*MNNSelectUnaryFunctionForInt8)(int opType);
#endif
    // B matrix is sparsed
    typedef void(*MNNPackedSparseMatMul)(float* C, const float* A, const float* B, size_t eSize, const size_t* parameter, const float* postParameters, const float* bias, unsigned int* NNZMap, int* dataOffsetMap);
    void(*MNNAdjustOptimalSparseKernel)(int& sparseBlockOC, MNNPackedSparseMatMul& packedSparseMatMul);
    /**Lowp Backend Setting*/
    void(*MNNFp32ToLowp)(const float* src, int16_t* dst, size_t size);
    void(*MNNLowpToFp32)(const int16_t* src, float* dst, size_t size);
    int bytes; // Byte for float
    int matmulBytes = 0; // Special bytes for dense matmul, C = A*B, A, B is matmulBytes, C is bytes. If 0, means the same as bytes

    /**NC4HW4's Functions*/
    int pack;
    // For pack * bytes > 16
    MNNCopyWithStride(*MNNSelectBlitFunction)(int blitBytes) = nullptr;

    void(*MNNPackCUnitInt16)(int16_t* dst, const int16_t* src, size_t area, size_t depth, int* areaOffset);
    void(*MNNUnpackCUnitInt16)(int16_t* dst, const int16_t* src, size_t area, size_t depth, int* areaOffset);
    void(*MNNPackCUnitTransposeInt16)(int16_t* dst, const int16_t* src, size_t area, size_t depth, int* areaOffset);
    void(*MNNUnpackCUnitTransposeInt16)(int16_t* dst, const int16_t* src, size_t area, size_t depth, int* areaOffset);

    void(*MNNPackCUnitInt8)(int8_t* dst, const int8_t* src, size_t area, size_t depth, int* areaOffset);
    void(*MNNUnpackCUnitInt8)(int8_t* dst, const int8_t* src, size_t area, size_t depth, int* areaOffset);
    void(*MNNPackCUnitTransposeInt8)(int8_t* dst, const int8_t* src, size_t area, size_t depth, int* areaOffset);
    void(*MNNUnpackCUnitTransposeInt8)(int8_t* dst, const int8_t* src, size_t area, size_t depth, int* areaOffset);

    void(*MNNPackCUnit)(float* dst, const float* src, size_t area, size_t depth, int* areaOffset);
    void(*MNNUnpackCUnit)(float* dst, const float* src, size_t area, size_t depth, int* areaOffset);
    void(*MNNPackCUnitTranspose)(float* dst, const float* src, size_t area, size_t depth, int* areaOffset);
    void(*MNNUnpackCUnitTranspose)(float* dst, const float* src, size_t area, size_t depth, int* areaOffset);

    // NC4HW4's compute function
    void(*MNNConvRunForLineDepthwise)(float* dst, const float* src, const float* weight, size_t width, size_t src_w_setup,
                                    size_t fw, size_t fh, size_t dilateX_step, size_t dilateY_step, size_t height,
                                    size_t srcHStep, size_t dstHStep, const float* bias, const float* parameters);
    void(*MNNAxByClampBroadcastUnit)(float* C, const float* A, const float* B, size_t width, size_t cStride, size_t aStride, size_t height, const float* parameters);
    void(*MNNMatrixAdd)(float* C, const float* A, const float* B, size_t widthC4, size_t cStride, size_t aStride,
                      size_t bStride, size_t height);
    void(*MNNMatrixSub)(float* C, const float* A, const float* B, size_t widthC4, size_t cStride, size_t aStride,
                      size_t bStride, size_t height);
    void(*MNNStrassenMergeCFunction)(float* c11, float* c12, float* c21, float* c22, float* xAddr, size_t cStride, size_t eSub, size_t hSub);
    void(*MNNScaleAndAddBias)(float* dst, const float* src, const float* bias, const float* alpha, size_t planeNumber, size_t biasNumber);
    void(*MNNGridSampleComputeCord)(float* dst, const float* src, size_t inH, size_t inW, size_t outH, size_t outW, bool alignCorners);
    void(*MNNGridSampleInterp)(float* outputPtr, const float* inputPtr, const float* cordPtr, size_t inH, size_t inW, size_t outW, size_t channelCUnit, size_t inOffset, size_t outOffset, bool sampleMode, bool padMode);
    void (*MNNGridSampleInterpGrad)(float* outputPtr, float* inputPtr, const float* cordPtr, size_t inH, size_t inW, size_t outW, size_t channelCUnit, size_t inOffset, size_t outOffset, bool sampleMode, bool padMode);

    void(*MNNGridSampleComputeCord3D)(float* dst, const float* src, size_t inD, size_t inH, size_t inW, size_t outD, size_t outH, size_t outW, bool alignCorners);
    void(*MNNGridSampleInterp3D)(float* outputPtr, const float* inputPtr, const float* cordPtr, size_t inD, size_t inH, size_t inW, size_t outW, size_t channelCUnit, size_t inOffset, size_t outOffset, bool sampleMode, bool padMode) = nullptr;
    void(*MNNRoiPoolingMax)(float* dst, const float* src, int hLen, int wLen, int iw);
    void(*MNNRoiAlignMax)(float* dst, const float* src, const std::vector<std::vector<int>> &vecPos, const std::vector<std::vector<float>> &vecArea, int samplingRatioArea, int pooledHeight, int pooledWidth);
    void(*MNNRoiAlignAvg)(float* dst, const float* src, const std::vector<std::vector<int>> &vecPos, const std::vector<std::vector<float>> &vecArea, int samplingRatioArea, int pooledHeight, int pooledWidth);

    float penalty;

    void(*MNNCopyC4WithStride)(const float* source, float* dest, size_t srcStride, size_t dstStride, size_t count);
    void(*MNNAddC4WithStride)(const float* source, float* dest, size_t srcStride, size_t dstStride, size_t count);

    typedef void (*WinoTransPackFunc)(float* srcBlock, float* dstStart, size_t dstStep);
    WinoTransPackFunc(*chooseWinoSourceTransformPack)(int k, int w, int ePack, int lPack, int packCUnit);

    typedef void (*WinoUnrollTransFunc)(const float* srcBlock, float* dstStart, size_t srcRowStep, size_t dstRowStep, size_t srcStep, size_t dstStep);
    typedef void (*WinoUnrollDestTransFunc)(const float* srcBlock, float* dstStart,  const float* bias, const float* postParameters, size_t srcRowStep, size_t dstRowStep, size_t srcStep, size_t dstStep);
    WinoUnrollTransFunc(*chooseWinoSourceUnrollTransform)(int k, int w);
    void(*chooseWinoDestUnrollTransform)(WinoUnrollDestTransFunc *destFunctions, size_t maxUnit, int k, int h);

    void(*MNNDeconvRunForUnitDepthWise)(const float* dst, float* src, const float* weight, size_t fw, size_t fh,
                                      size_t weight_y_step, size_t dilateX_step, size_t dilateY_step);
    void(*MNNDeconvRunForLineDepthwise)(const float* dst, float* src, const float* weight, size_t width, size_t src_w_setup,
                                      size_t fw, size_t fh, size_t dilateX_step, size_t dilateY_step);
    void(*MNNDepthwiseConvFastKernel)(float* dst, const float* src, const float* weight, size_t width, size_t src_w_setup,
                                    size_t fw, size_t fh, size_t dilateX_step, size_t dilateY_step, size_t height,
                                    size_t srcHStep, size_t dstHStep, const float* bias, const float* parameters) = nullptr;
    void(*MNNReluWithSlopeChannel)(float* dst, const float* src, const float* slope, size_t sizeQuad, size_t depthQuad);
    void(*MNNPoolingAvg)(const void* channelInput, int inputWidth, int inputHeight, void *channelOutput,
                           int outputWidth, int outputHeight, int kernelWidth, int kernelHeight, int strideWidth,
                           int strideHeight, int padWidth, int padHeight, int padType, int countType);
    void(*MNNPoolingMax)(const void* channelInput, int inputWidth, int inputHeight, void *channelOutput,
                           int outputWidth, int outputHeight, int kernelWidth, int kernelHeight, int strideWidth,
                           int strideHeight, int padWidth, int padHeight, int padType, int countType);

    void(*MNNPoolingMaxWithRedice)(const void* channelInput, int inputWidth, int inputHeight, void *channelOutput,
                           int outputWidth, int outputHeight, int kernelWidth, int kernelHeight, int strideWidth,
                           int strideHeight, int padWidth, int padHeight, int padType, int countType, int *RediceOutput);
    // ImageProcess Funtions
    void(*MNNRGBAToBGRA)(const unsigned char* source, unsigned char* dest, size_t count);
    void(*MNNNV21ToRGBA)(const unsigned char* source, unsigned char* dest, size_t count);
    void(*MNNNV21ToRGB)(const unsigned char* source, unsigned char* dest, size_t count);
    void(*MNNNV21ToBGRA)(const unsigned char* source, unsigned char* dest, size_t count);
    void(*MNNNV21ToBGR)(const unsigned char* source, unsigned char* dest, size_t count);
    void(*MNNC1ToFloatC1)(const unsigned char* source, float* dest, const float* mean, const float* normal, size_t count);
    void(*MNNC3ToFloatC3)(const unsigned char* source, float* dest, const float* mean, const float* normal, size_t count);
    void(*MNNC3ToFloatRGBA)(const unsigned char* source, float* dest, const float* mean, const float* normal, size_t count);
    void(*MNNsampleBilinearCommon)(const unsigned char* source, unsigned char* dest, MNN::CV::Point* points, size_t count,
                                size_t iw, size_t ih, size_t yStride, size_t bpp);
    void(*MNNSamplerC4Nearest)(const unsigned char* source, unsigned char* dest, MNN::CV::Point* points, size_t sta,
                         size_t count, size_t capacity, size_t iw, size_t ih, size_t yStride);
    void(*MNNSamplerC4Bilinear)(const unsigned char* source, unsigned char* dest, MNN::CV::Point* points, size_t sta,
                          size_t count, size_t capacity, size_t iw, size_t ih, size_t yStride);
    void(*MNNSampleC4Bilinear)(const unsigned char* source, unsigned char* dest, MNN::CV::Point* points, size_t sta,
                              size_t count, size_t capacity, size_t iw, size_t ih, size_t yStride);
    void(*MNNSampleBilinear)(const unsigned char* source, unsigned char* dest, MNN::CV::Point* points, size_t count,
                                      size_t iw, size_t ih, size_t yStride, size_t bpp);

    void(*MNN4BitcopyWithStride)(uint8_t* dstO, const uint8_t* srcO, int size, int stride, int ds);
    void(*MNN2BitcopyWithStride)(uint8_t* dstO, const uint8_t* srcO, int size, int stride, int ds);
    void(*MNN1BitcopyWithStride)(uint8_t* dstO, const uint8_t* srcO, int size, int stride, int ds);
    void(*MNN4BitcopyFast)(uint8_t* dstO, const uint8_t* srcO, int size, int stride, int ds);
    void(*MNN2BitcopyFast)(uint8_t* dstO, const uint8_t* srcO, int size, int stride, int ds);
    void(*MNN1BitcopyFast)(uint8_t* dstO, const uint8_t* srcO, int size, int stride, int ds);
    void(*MNNAccumulateSequenceNumber)(float* dst, const float* src, int size);
    void(*MNNSumByAxisLForMatmul_A)(float* dest, int8_t* source, const float* dequantScale, ssize_t realDstCount, SumByAxisParams sumParams);
    void(*MNNReorderWeightInt4)(uint8_t* dest, const uint8_t* source, int32_t* shape, size_t size, float* kernelsum);
    void(*MNNSumWeightInt8)(float* kernlesum, int8_t* source, size_t outside, size_t reduceAxis, size_t hP, size_t lP);

    MatmulRelatedFunctions backendMatmulRelatedFunctions;
    MatmulRelatedFunctions sme2MatmulRelatedFuncions;
};
void MNNCoreFunctionInit();
CoreFunctions* MNNGetCoreFunctions();
};

#endif /* CommonOptFunction_h */
