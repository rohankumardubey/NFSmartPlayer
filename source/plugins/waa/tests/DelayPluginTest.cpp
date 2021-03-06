/*
 * Copyright (c) 2017 Spotify AB.
 *
 * Licensed to the Apache Software Foundation (ASF) under one
 * or more contributor license agreements.  See the NOTICE file
 * distributed with this work for additional information
 * regarding copyright ownership.  The ASF licenses this file
 * to you under the Apache License, Version 2.0 (the
 * "License"); you may not use this file except in compliance
 * with the License.  You may obtain a copy of the License at
 *
 *   http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing,
 * software distributed under the License is distributed on an
 * "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY
 * KIND, either express or implied.  See the License for the
 * specific language governing permissions and limitations
 * under the License.
 */
#include <boost/test/unit_test.hpp>

#include "DelayPlugin.h"

BOOST_AUTO_TEST_SUITE(DelayPluginTests)

BOOST_AUTO_TEST_CASE(testLocalRenderTimeIsZero) {
  nlohmann::json delay_node = {
      {"id", "gn-1"},
      {"kind", "com.nativeformat.plugin.waa.delay"},
      {"config", {}},
      {"params",
       {{"delayTime",
         {{{"name", "setValueAtTime"},
           {"args", {{"value", 0.25}, {"startTime", 0}}}}}}}},
  };
  nfgrapher::Node n = delay_node;
  nfgrapher::contract::DelayNodeInfo dn(n);
  nativeformat::plugin::waa::DelayPlugin plugin(dn, 2, 44100.0, nullptr);
  BOOST_CHECK_EQUAL(plugin.localRenderSampleIndex(0), 0);
}

BOOST_AUTO_TEST_SUITE_END()
