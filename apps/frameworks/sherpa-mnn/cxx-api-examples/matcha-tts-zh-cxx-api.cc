// cxx-api-examples/matcha-tts-zh-cxx-api.cc
//
// Copyright (c)  2025  Xiaomi Corporation

// This file shows how to use sherpa-onnx CXX API
// for Chinese TTS with MatchaTTS.
//
// clang-format off
/*
Usage

wget https://github.com/k2-fsa/sherpa-onnx/releases/download/tts-models/matcha-icefall-zh-baker.tar.bz2
tar xvf matcha-icefall-zh-baker.tar.bz2
rm matcha-icefall-zh-baker.tar.bz2

wget https://github.com/k2-fsa/sherpa-onnx/releases/download/vocoder-models/hifigan_v2.onnx

./matcha-tts-zh-cxx-api

 */
// clang-format on

#include <string>

#include "sherpa-mnn/c-api/cxx-api.h"

static int32_t ProgressCallback(const float *samples, int32_t num_samples,
                                float progress, void *arg) {
  fprintf(stderr, "Progress: %.3f%%\n", progress * 100);
  // return 1 to continue generating
  // return 0 to stop generating
  return 1;
}

int32_t main(int32_t argc, char *argv[]) {
  using namespace sherpa_mnn::cxx;  // NOLINT
  OfflineTtsConfig config;
  config.model.matcha.acoustic_model =
      "./matcha-icefall-zh-baker/model-steps-3.onnx";
  config.model.matcha.vocoder = "./hifigan_v2.onnx";
  config.model.matcha.lexicon = "./matcha-icefall-zh-baker/lexicon.txt";
  config.model.matcha.tokens = "./matcha-icefall-zh-baker/tokens.txt";
  config.model.matcha.dict_dir = "./matcha-icefall-zh-baker/dict";
  config.model.num_threads = 1;

  // If you don't want to see debug messages, please set it to 0
  config.model.debug = 1;

  // clang-format off
  config.rule_fsts = "./matcha-icefall-zh-baker/phone.fst,./matcha-icefall-zh-baker/date.fst,./matcha-icefall-zh-baker/number.fst";  // NOLINT
  // clang-format on

  std::string filename = "./generated-matcha-zh-cxx.wav";
  std::string text =
      "当夜幕降临，星光点点，伴随着微风拂面，我在静谧中感受着时光的流转，思念如"
      "涟漪荡漾，梦境如画卷展开，我与自然融为一体，沉静在这片宁静的美丽之中，感"
      "受着生命的奇迹与温柔."
      "某某银行的副行长和一些行政领导表示，他们去过长江和长白山; "
      "经济不断增长。2024年12月31号，拨打110或者18920240511。123456块钱。";

  auto tts = OfflineTts::Create(config);
  int32_t sid = 0;
  float speed = 1.0;  // larger -> faster in speech speed

#if 0
  // If you don't want to use a callback, then please enable this branch
  GeneratedAudio audio = tts.Generate(text, sid, speed);
#else
  GeneratedAudio audio = tts.Generate(text, sid, speed, ProgressCallback);
#endif

  WriteWave(filename, {audio.samples, audio.sample_rate});

  fprintf(stderr, "Input text is: %s\n", text.c_str());
  fprintf(stderr, "Speaker ID is is: %d\n", sid);
  fprintf(stderr, "Saved to: %s\n", filename.c_str());

  return 0;
}
