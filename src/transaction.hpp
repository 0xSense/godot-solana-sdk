#ifndef SOLANA_SDK_TRANSACTION_HPP
#define SOLANA_SDK_TRANSACTION_HPP

#include "../wrapper/wrapper.h"

#include "pubkey.hpp"
#include "account.hpp"
#include "solana_node.hpp"

#include <godot_cpp/classes/node.hpp>

namespace godot{

class Transaction : public SolanaNode {
    GDCLASS(Transaction, Node)

private:
    Array instructions;
    Variant payer;
    bool signed_transaction = false;
    Array signers;

    void _update_pointer() override;
    void _free_pointer() override;
    void _get_property_list(List<PropertyInfo> *p_list) const;

protected:
    static void _bind_methods();

public:
    Transaction();

    void set_instructions(const Array& p_value);
    Array get_instructions();

    void set_payer(const Variant& p_value);
    Variant get_payer();

    bool _set(const StringName &p_name, const Variant &p_value);
	bool _get(const StringName &p_name, Variant &r_ret) const;

    void set_signers(const Array& p_value);
    Array get_signers();

    void set_signed_transaction(const bool p_value);
    bool get_signed_transaction();

    Error serialize();

    void create_signed_with_payer(Array instructions, Variant payer, Array signers, Variant latest_blockhash);

    ~Transaction();
};
}

#endif