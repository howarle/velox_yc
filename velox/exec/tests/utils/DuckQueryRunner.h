/*
 * Copyright (c) Facebook, Inc. and its affiliates.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */
#pragma once

#include "velox/exec/tests/utils/ReferenceQueryRunner.h"

namespace facebook::velox::exec::test {

class DuckQueryRunner : public ReferenceQueryRunner {
 public:
  DuckQueryRunner();

  /// Supports AggregationNode and WindowNode with optional ProjectNode on top.
  /// Assumes that source of AggregationNode or Window Node is 'tmp' table.
  std::optional<std::string> toSql(const core::PlanNodePtr& plan) override;

  /// Creates 'tmp' table with 'input' data and runs 'sql' query. Returns
  /// results according to 'resultType' schema.
  std::multiset<std::vector<velox::variant>> execute(
      const std::string& sql,
      const std::vector<RowVectorPtr>& input,
      const RowTypePtr& resultType) override;

 private:
  std::optional<std::string> toSql(
      const std::shared_ptr<const core::AggregationNode>& aggregationNode);

  std::optional<std::string> toSql(
      const std::shared_ptr<const core::WindowNode>& windowNode);

  std::optional<std::string> toSql(
      const std::shared_ptr<const core::ProjectNode>& projectNode);

  std::unordered_set<std::string> aggregateFunctionNames_;
};

} // namespace facebook::velox::exec::test
