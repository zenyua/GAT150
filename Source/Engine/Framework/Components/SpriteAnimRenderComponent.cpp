#include "SpriteAnimRenderComponent.h"
#include "Renderer/Renderer.h"
#include "Framework/Actor.h"
#include <Framework/Resource/ResourceManager.h>

namespace ringo {

	CLASS_DEFINITION(SpriteAnimRenderComponent)

	bool SpriteAnimRenderComponent::Initialize()
	{
		SpriteComponent::Initialize();

		SetSequence(defaultSequenceName);
		UpdateSource();

		return true;
	}

	void SpriteAnimRenderComponent::Update(float dt)
	{
		frameTimer -= dt;
		if (frameTimer <= 0) {
			frameTimer = 1.0f / m_sequence->fps;
			frame++;
			if (frame > m_sequence->endFrame) {
				frame = (m_sequence->loop) ? m_sequence->startFrame : m_sequence->endFrame;
			}
		}

		UpdateSource();
	}

	void SpriteAnimRenderComponent::SetSequence(const std::string& name)
	{
		//prevent setting sequence again
		if (m_sequence && m_sequence->name == name) return;

		if (m_sequences.find(name) != m_sequences.end()) {
			//set new sequence
			m_sequence = &m_sequences[name];
			//set texure
			if(m_sequence->texture) m_texture = m_sequence->texture;
			//reset frame information
			frame = m_sequence->startFrame;
			frameTimer = 1.0f / m_sequence->fps;
		}
	}

	void SpriteAnimRenderComponent::UpdateSource()
	{
		vec2 cellSize = m_texture->GetSize() / vec2{ m_sequence->numColumns, m_sequence->numRows };
		int column = (frame - 1) % m_sequence->numColumns;
		int row = (frame - 1) / m_sequence->numColumns;

		//set source rect ...
		source.x = (int)(column * cellSize.x);
		source.y = (int)(row * cellSize.y);
		source.w = (int)(cellSize.x);
		source.h = (int)(cellSize.y);
	}

	void SpriteAnimRenderComponent::Read(const json_t& value) {
		SpriteComponent::Read(value);

		// read in animation sequences
		if (HAS_DATA(value, sequences) && GET_DATA(value, sequences).IsArray())
		{
			for (auto& sequenceValue : GET_DATA(value, sequences).GetArray())
			{
				AnimSequence sequence;

				READ_NAME_DATA(sequenceValue, "name", sequence.name);
				READ_NAME_DATA(sequenceValue, "fps", sequence.fps);
				READ_NAME_DATA(sequenceValue, "numColumns", sequence.numColumns);
				READ_NAME_DATA(sequenceValue, "numRows", sequence.numRows);
				READ_NAME_DATA(sequenceValue, "startFrame", sequence.startFrame);
				READ_NAME_DATA(sequenceValue, "endFrame", sequence.endFrame);

				// read texture
				std::string textureName;
				READ_DATA(sequenceValue, textureName);
				sequence.texture = GET_RESOURCE(Texture, textureName, g_renderer);

				m_sequences[sequence.name] = sequence;
			}
		}

		if (!READ_DATA(value, defaultSequenceName))
		{
			// if default sequence not specified, use the first sequence in the sequences map
			defaultSequenceName = m_sequences.begin()->first;
		}
	}
}


