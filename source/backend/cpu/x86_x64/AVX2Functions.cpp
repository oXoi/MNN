//
//  AVX2Functions.cpp
//  MNN
//
//  Created by MNN on b'2021/05/17'.
//  Copyright © 2018, Alibaba Group Holding Limited
//

#include "AVX2Functions.hpp"
#include "AVX2Backend.hpp"
#include "avx/FunctionSummary.hpp"
#include "avxfma/FunctionSummary.hpp"
#include "avx512/FunctionSummary.hpp"
#include "sse/FunctionSummary.hpp"
namespace MNN {
static int geP, glP, ghP;
static CoreFunctions* gAVX2CoreFunctions = nullptr;
static CoreInt8Functions* gAVX2CoreInt8Functions = nullptr;
static void _MNNGetMatMulPackMode(int* eP, int *lP, int* hP) {
    *eP = geP;
    *lP = glP;
    *hP = ghP;
}

#ifndef MNN_USE_AVX
bool AVX2Functions::init(int cpuFlags) {
    return false;
}
#else

bool AVX2Functions::init(int cpuFlags) {
    gAVX2CoreFunctions = new CoreFunctions;
    auto coreFunction = gAVX2CoreFunctions;
    gAVX2CoreInt8Functions = new CoreInt8Functions;
    // Init default functions
    *coreFunction = *MNNGetCoreFunctions();
    *gAVX2CoreInt8Functions = *MNNGetInt8CoreFunctions();
    _AVX_MNNInt8FunctionInit(gAVX2CoreInt8Functions);
    // Init AVX2
    coreFunction->MNNGetMatMulPackMode = _MNNGetMatMulPackMode;
    geP = 24;
    glP = 1;
    ghP = 4;
    _AVX_ReorderInit(coreFunction);

    coreFunction->MNNPackedMatMul       = _AVX_MNNPackedMatMul;
    coreFunction->MNNPackedMatMulRemain = _AVX_MNNPackedMatMulRemain;
#ifdef MNN_CPU_WEIGHT_DEQUANT_GEMM
    coreFunction->MNNPackedMatMul_int8       = _AVX_MNNPackedMatMul_int8;
    coreFunction->MNNPackedMatMulRemain_int8 = _AVX_MNNPackedMatMulRemain_int8;
#endif

#ifdef MNN_LOW_MEMORY
    coreFunction->MNNAbsMax = _AVX_MNNAbsMaxFP32;
    coreFunction->MNNDynamicQuant = _AVX_MNNDynamicQuant;
    coreFunction->MNNAsyQuantFunc = _AVX_MNNAsyQuantFunc;
    coreFunction->MNNAsyQuantInfo = _AVX_MNNAsyQuantInfo;
#endif
    coreFunction->MNNPackC4ForMatMul_A  = _AVX_MNNPackC4ForMatMul_A;
    coreFunction->MNNPackForMatMul_B    = _AVX_MNNPackForMatMul_B;
    coreFunction->MNNComputeMatMulForE_1 = _AVX_MNNComputeMatMulForE_1;
    coreFunction->MNNComputeMatMulForH_1 = _AVX_MNNComputeMatMulForH_1;
    // Dynamic Quant
    coreFunction->MNNCountMaxMinValue = _AVX_MNNCountMinMaxValue;
    

    // For Packed Functions
    coreFunction->pack = 8;
    _AVX_ExtraInit(coreFunction);
    // Winograd
    _AVX_WinogradInit(coreFunction);
    if (cpuFlags & libyuv::kCpuHasFMA3) {
        coreFunction->MNNPackedMatMul       = _AVX_MNNPackedMatMulFMA;
        coreFunction->MNNPackedMatMulRemain = _AVX_MNNPackedMatMulRemainFMA;
        coreFunction->MNNComputeMatMulForE_1 = _AVX_MNNComputeMatMulForE_1FMA;
        coreFunction->MNNComputeMatMulForH_1 = _AVX_MNNComputeMatMulForH_1FMA;
        _AVX_ExtraInitFMA(coreFunction);
    }
#ifdef MNN_AVX512
    if ((cpuFlags & libyuv::kCpuHasAVX512VNNI)
        || (cpuFlags & libyuv::kCpuHasAVX512VL)
        || (cpuFlags & libyuv::kCpuHasAVX512BW)
        || (cpuFlags & libyuv::kCpuHasAVX512VBMI)
        || (cpuFlags & libyuv::kCpuHasAVX512VBITALG)
        || (cpuFlags & libyuv::kCpuHasAVX512VPOPCNTDQ)
        || (cpuFlags & libyuv::kCpuHasAVX512VBMI2)
        ) {
        coreFunction->pack = 16;
        _AVX512_ReorderInit(coreFunction);
        _AVX512_ExtraInit(coreFunction);
        _AVX512_WinogradInit(coreFunction);
        coreFunction->MNNPackForMatMul_B    = _AVX512_MNNPackForMatMul_B;
        coreFunction->MNNPackC4ForMatMul_A  = _AVX512_MNNPackC8ForMatMul_A;
        coreFunction->MNNPackedMatMul = _AVX512_MNNPackedMatMul;
        coreFunction->MNNPackedMatMulRemain = _AVX512_MNNPackedMatMulRemain;
        geP = 48;
        ghP = 8;
        glP = 1;
        _AVX512_MNNInt8FunctionInit(gAVX2CoreInt8Functions, cpuFlags & libyuv::kCpuHasAVX512VNNI);
        memcpy(coreFunction->MNNPackedMatMulOC16Functions, _AVX512_MNNPackedMatMulOC16Functions,
            sizeof(MNN::CoreFunctions::MNNPackedMatMulKernel) * AVX512_INPUT_TILE_MAX);
        memcpy(coreFunction->MNNPackedMatMulOC32Functions, _AVX512_MNNPackedMatMulOC32Functions,
            sizeof(MNN::CoreFunctions::MNNPackedMatMulKernel) * AVX512_INPUT_TILE_MAX);
        memcpy(coreFunction->MNNPackedMatMulOC48Functions, _AVX512_MNNPackedMatMulOC48Functions,
            sizeof(MNN::CoreFunctions::MNNPackedMatMulKernel) * AVX512_INPUT_TILE_MAX);
    }
#endif
    {
        coreFunction->backendMatmulRelatedFunctions.MNNGetMatMulPackMode = coreFunction->MNNGetMatMulPackMode;
        coreFunction->backendMatmulRelatedFunctions.MNNPackC4ForMatMul_A = coreFunction->MNNPackC4ForMatMul_A;
        coreFunction->backendMatmulRelatedFunctions.MNNPackForMatMul_B = coreFunction->MNNPackForMatMul_B;
        coreFunction->backendMatmulRelatedFunctions.MNNPackedMatMul = coreFunction->MNNPackedMatMul;
        coreFunction->backendMatmulRelatedFunctions.MNNPackedMatMulRemain = coreFunction->MNNPackedMatMulRemain;
        coreFunction->backendMatmulRelatedFunctions.Int8GemmKernel = gAVX2CoreInt8Functions->Int8GemmKernel;
        coreFunction->backendMatmulRelatedFunctions.Int8GemmKernelFast = gAVX2CoreInt8Functions->Int8GemmKernelFast;
        coreFunction->backendMatmulRelatedFunctions.Int8GemmKernel_W4 = gAVX2CoreInt8Functions->Int8GemmKernel_W4;
        coreFunction->backendMatmulRelatedFunctions.MNNGetGemmUnit = gAVX2CoreInt8Functions->MNNGetGemmUnit;
        coreFunction->backendMatmulRelatedFunctions.MNNPackC4Int8ForMatMul_A = gAVX2CoreInt8Functions->MNNPackC4Int8ForMatMul_A;
    }
    return true;
}
#endif

CoreFunctions* AVX2Functions::get() {
    return gAVX2CoreFunctions;
}
CoreInt8Functions* AVX2Functions::getInt8() {
    return gAVX2CoreInt8Functions;
}
};
