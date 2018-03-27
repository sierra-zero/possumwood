#pragma once

#include <vector>
#include <memory>

#include "io/json.h"

#include "data.h"
#include "metadata.h"

namespace dependency_graph {

class Node;

/// A data storage class used by Node implementation.
/// Each data value is strongly typed, and stored as base class pointer.
class Datablock {
	public:
		Datablock(const MetadataHandle& meta);

		Datablock(const Datablock& d);
		Datablock& operator = (const Datablock& d);

		template<typename T>
		const T& get(size_t index) const;

		template<typename T>
		void set(size_t index, const T& value);

		void reset(size_t index);

		const BaseData& data(size_t index) const;
		BaseData& data(size_t index);

		const MetadataHandle& meta() const;

	private:
		std::vector<std::unique_ptr<BaseData>> m_data;
		MetadataHandle m_meta;
};

}
