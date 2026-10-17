#include <pl/Mod.hpp>

namespace kao_mb_shader_bridge {

class KaoMBShaderBridge {
public:
    static KaoMBShaderBridge& instance() {
        static KaoMBShaderBridge mod;
        return mod;
    }

    KaoMBShaderBridge() : mSelf(*ll::mod::NativeMod::current()) {}

    [[nodiscard]] ll::mod::NativeMod& getSelf() const {
        return mSelf;
    }

    bool load() {
        getSelf().getLogger().info(
            "Kao MB Shader Bridge loaded. Diagnostic build only; shader redirect is not enabled yet."
        );
        return true;
    }

    bool enable() {
        getSelf().getLogger().info(
            "Kao MB Shader Bridge enabled. Waiting for verified MB Loader integration."
        );
        return true;
    }

    bool disable() {
        getSelf().getLogger().info("Kao MB Shader Bridge disabled.");
        return true;
    }

    bool unload() {
        getSelf().getLogger().info("Kao MB Shader Bridge unloaded.");
        return true;
    }

private:
    ll::mod::NativeMod& mSelf;
};

} // namespace kao_mb_shader_bridge

PL_REGISTER_MOD(
    kao_mb_shader_bridge::KaoMBShaderBridge,
    kao_mb_shader_bridge::KaoMBShaderBridge::instance()
)
