#include "RenderPass.h"

VkRenderPass RenderPass::get() const
{
	return renderPass;
}

void RenderPass::create(VkDevice device, VkFormat swapchainFormat)
{
	VkAttachmentDescription attachmentDesc{};

		attachmentDesc.format = swapchainFormat;
		attachmentDesc.samples = VK_SAMPLE_COUNT_1_BIT;

		attachmentDesc.loadOp = VK_ATTACHMENT_LOAD_OP_CLEAR;
		attachmentDesc.storeOp = VK_ATTACHMENT_STORE_OP_STORE;

		attachmentDesc.stencilLoadOp = VK_ATTACHMENT_LOAD_OP_DONT_CARE;
		attachmentDesc.stencilStoreOp = VK_ATTACHMENT_STORE_OP_DONT_CARE;

		attachmentDesc.initialLayout = VK_IMAGE_LAYOUT_UNDEFINED;
		attachmentDesc.finalLayout = VK_IMAGE_LAYOUT_PRESENT_SRC_KHR;

	VkAttachmentReference attachmentReference{};
	
		attachmentReference.attachment = 0;
		attachmentReference.layout = VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL;

	VkSubpassDescription subpassDesc{};

		subpassDesc.pipelineBindPoint = VK_PIPELINE_BIND_POINT_GRAPHICS;

		subpassDesc.colorAttachmentCount = 1;
		subpassDesc.pColorAttachments = &attachmentReference;

	VkSubpassDependency dependecy{};

		dependecy.srcSubpass = VK_SUBPASS_EXTERNAL;
		dependecy.dstSubpass = 0;

		dependecy.srcStageMask = VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT;
		dependecy.dstStageMask = VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT;

		dependecy.srcAccessMask = 0;
		dependecy.dstAccessMask = VK_ACCESS_COLOR_ATTACHMENT_WRITE_BIT;

	VkRenderPassCreateInfo renderPassInfo{};

		renderPassInfo.sType = VK_STRUCTURE_TYPE_RENDER_PASS_CREATE_INFO;

		renderPassInfo.attachmentCount = 1;
		renderPassInfo.pAttachments = &attachmentDesc;

		renderPassInfo.subpassCount = 1;
		renderPassInfo.pSubpasses = &subpassDesc;

		renderPassInfo.dependencyCount = 1;
		renderPassInfo.pDependencies = &dependecy;


		if (vkCreateRenderPass(device, &renderPassInfo, nullptr, &renderPass) != VK_SUCCESS)
		{
			throw std::runtime_error("Failed to create render pass!\n");
		}

		std::cout << "Successfully created renderpass!\n";
}

void RenderPass::cleanup(VkDevice device)
{
	if (renderPass != VK_NULL_HANDLE)
	{
		vkDestroyRenderPass(device, renderPass, nullptr);

		renderPass = VK_NULL_HANDLE;
	}
}