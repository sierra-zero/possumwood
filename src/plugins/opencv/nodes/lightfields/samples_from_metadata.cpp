#include <possumwood_sdk/node_implementation.h>

#include <opencv2/opencv.hpp>

#include <actions/traits.h>

#include <lightfields/metadata.h>
#include "lightfield_pattern.h"
#include "lightfield_samples.h"
#include "tools.h"
#include "lightfields.h"

namespace {

dependency_graph::InAttr<lightfields::Metadata> a_meta;
dependency_graph::OutAttr<possumwood::opencv::LightfieldSamples> a_samples;

dependency_graph::State compute(dependency_graph::Values& data) {
	// metadata instance - just a bunch of JSON dictionaries extracted from the image
	const lightfields::Metadata& meta = data.get(a_meta);

	// get the data from dicts and make it into a pattern
	const lightfields::Pattern pattern = lightfields::Pattern::fromMetadata(meta);

	// comvert the pattern to the samples instance
	data.set(a_samples, std::move(possumwood::opencv::LightfieldSamples(pattern)));

	return dependency_graph::State();
}

void init(possumwood::Metadata& meta) {
	meta.addAttribute(a_meta, "metadata", lightfields::Metadata(), possumwood::AttrFlags::kVertical);
	meta.addAttribute(a_samples, "samples", possumwood::opencv::LightfieldSamples(), possumwood::AttrFlags::kVertical);

	meta.addInfluence(a_meta, a_samples);

	meta.setCompute(compute);
}


possumwood::NodeImplementation s_impl("opencv/lightfields/samples_from_metadata", init);

}
