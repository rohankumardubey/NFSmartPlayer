/*
 * Copyright (c) 2016 Spotify AB.
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
#include "EQPluginFactory.h"

#include "EQPlugin.h"
#include "FilterPlugin.h"

namespace nativeformat {
namespace plugin {
namespace eq {

EQPluginFactory::EQPluginFactory() {}

EQPluginFactory::~EQPluginFactory() {}

std::shared_ptr<Plugin> EQPluginFactory::createPlugin(
    const nfgrapher::Node &grapher_node, const std::string &graph_id,
    const NF_PLUGIN_RESOLVE_CALLBACK &resolve_callback, int channels,
    double samplerate, const std::shared_ptr<plugin::Plugin> &child_plugin,
    const std::string &session_id) {
  if (grapher_node.kind == nfgrapher::contract::Eq3bandNodeInfo::kind()) {
    nfgrapher::contract::Eq3bandNodeInfo eq_node(grapher_node);
    return std::make_shared<EQPlugin>(eq_node, channels, samplerate,
                                      child_plugin);
  } else if (grapher_node.kind == nfgrapher::contract::FilterNodeInfo::kind()) {
    nfgrapher::contract::FilterNodeInfo filter_node(grapher_node);
    return std::make_shared<FilterPlugin>(filter_node, channels, samplerate,
                                          child_plugin);
  }
  return nullptr;
}

std::vector<std::string> EQPluginFactory::identifiers() const {
  return {nfgrapher::contract::Eq3bandNodeInfo::kind(),
          nfgrapher::contract::FilterNodeInfo::kind()};
}

}  // namespace eq
}  // namespace plugin
}  // namespace nativeformat
