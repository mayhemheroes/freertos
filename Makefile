KERNEL_GITHUB=https://github.com/FreeRTOS/FreeRTOS-Kernel
KERNEL_COMMIT=32e581636f66504daa1a76afcc766be2a4b8a9de
PLUS_TCP_GITHUB=https://github.com/FreeRTOS/FreeRTOS-Plus-TCP
PLUS_TCP_COMMIT=19134e1dc5adce673fa2f19f032e9245d8fc44e4

.PHONY: sync-kernel sync-plus-tcp sync build

# Usage: $(call sync-repo,directory,github_url,commit_hash)
define sync-repo
	@if [ -d "$(1)" ]; then \
		if [ -n "$$(git status --porcelain $(1))" ]; then \
			echo "Error: $(1) has uncommitted changes"; \
			echo "Commit or stash changes before syncing"; \
			exit 1; \
		fi; \
	fi
	rm -rf $(1)
	mkdir -p $(1)
	curl -L $(2)/archive/$(3).tar.gz | tar xz --strip-components=1 -C $(1)
	echo "$(3)" > $(1)/.commit
	@echo "Synced $(1) to commit $(3)"
endef

sync-kernel:
	$(call sync-repo,freertos_kernel,$(KERNEL_GITHUB),$(KERNEL_COMMIT))

sync-plus-tcp:
	$(call sync-repo,freertos_plus_tcp,$(PLUS_TCP_GITHUB),$(PLUS_TCP_COMMIT))

sync: sync-kernel sync-plus-tcp
