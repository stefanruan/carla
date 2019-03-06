// Copyright (c) 2017 Computer Vision Center (CVC) at the Universitat Autonoma
// de Barcelona (UAB).
//
// This work is licensed under the terms of the MIT license.
// For a copy, see <https://opensource.org/licenses/MIT>.

#pragma once

#include "carla/Memory.h"
#include "carla/NonCopyable.h"
#include "carla/sensor/RawData.h"

/// @todo This shouldn't be exposed in this namespace.
#include "carla/client/World.h"
#include "carla/client/detail/EpisodeProxy.h"

namespace carla {
namespace sensor {

  /// Base class for all the objects containing data generated by a sensor.
  class SensorData
    : public EnableSharedFromThis<SensorData>,
      private NonCopyable {
  protected:

    SensorData(size_t frame_number, double timestamp, const rpc::Transform &sensor_transform)
      : _frame_number(frame_number),
		_timestamp(timestamp),
        _sensor_transform(sensor_transform) {}

    explicit SensorData(const RawData &data)
      : SensorData(data.GetFrameNumber(), data.GetTimestamp(), data.GetSensorTransform()) {}

  public:

    virtual ~SensorData() = default;

    /// Frame count when the data was generated.
    size_t GetFrameNumber() const {
      return _frame_number;
    }

    /// Time the data was generated.
    double GetTimestamp() const {
      return _timestamp;
    }

    /// Sensor's transform when the data was generated.
    const rpc::Transform &GetSensorTransform() const {
      return _sensor_transform;
    }

  protected:

    const auto &GetEpisode() const {
      return _episode;
    }

  private:

    /// @todo This shouldn't be exposed in this namespace.
    friend class client::detail::Simulator;
    client::detail::WeakEpisodeProxy _episode;

    const size_t _frame_number;

    const double _timestamp;

    const rpc::Transform _sensor_transform;
  };

} // namespace sensor
} // namespace carla
