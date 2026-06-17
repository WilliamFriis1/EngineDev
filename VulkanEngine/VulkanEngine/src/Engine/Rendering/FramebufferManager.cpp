#include "FramebufferManager.h"

void FramebufferManager::createFramebuffers(VkDevice device, VkRenderPass renderPass, const std::vector<VkImageView>& imageViews, const VkExtent2D& extent)
{
	framebuffers.resize(imageViews.size());

	for (size_t i = 0; i < imageViews.size(); i++)
	{
		VkImageView attachments[] = { imageViews[i] };

		VkFramebufferCreateInfo framebufferInfo{};

		framebufferInfo.sType = VK_STRUCTURE_TYPE_FRAMEBUFFER_CREATE_INFO;
		framebufferInfo.renderPass = renderPass;
		framebufferInfo.attachmentCount = 1;

		framebufferInfo.pAttachments = attachments;
		framebufferInfo.width = extent.width;
		framebufferInfo.height = extent.height;
		framebufferInfo.layers = 1;


		if (vkCreateFramebuffer(device, &framebufferInfo, nullptr, &framebuffers[i]) != VK_SUCCESS)
		{
			throw std::runtime_error("Failed to create framebuffer!\n");
		}

	}

	std::cout << "Successfully created framebuffers: " << framebuffers.size() << "!\n";
}

void FramebufferManager::cleanupFramebuffers(VkDevice device)
{
	for (auto framebuffer : framebuffers)
	{
		vkDestroyFramebuffer(device, framebuffer, nullptr);
	}
}