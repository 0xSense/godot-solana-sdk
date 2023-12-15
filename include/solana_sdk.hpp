#ifndef GDEXAMPLE_H
#define GDEXAMPLE_H

#include <godot_cpp/classes/node.hpp>
#include <hash.hpp>

namespace Godot {

class SolanaSDK : public Node {
    GDCLASS(SolanaSDK, Node)

private:
protected:
    static void _bind_methods();

public:
    const String MAINNET_URL = "https://api.mainnet.solana.com";
    const String DEVNET_URL = "https://api.devnet.solana.com";
    const String TESTNET_URL = "https://api.testnet.solana.com";
    const String LOCALHOST_URL = "http://127.0.0.1:8899";

    static const std::string SPL_TOKEN_ADDRESS;
    static const std::string SPL_ASSOCIATED_TOKEN_ADDRESS;

    SolanaSDK();
    static PackedByteArray bs58_decode(String str);
    static String bs58_encode(PackedByteArray input);
    static String bs64_encode(PackedByteArray bytes);
    static PackedByteArray bs64_decode(String input);

    ~SolanaSDK();
};
}

#endif
