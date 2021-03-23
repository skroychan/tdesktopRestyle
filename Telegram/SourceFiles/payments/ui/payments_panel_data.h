/*
This file is part of Telegram Desktop,
the official desktop application for the Telegram messaging service.

For license and copyright information please follow this link:
https://github.com/telegramdesktop/tdesktop/blob/master/LEGAL
*/
#pragma once

namespace Payments::Ui {

struct LabeledPrice {
	QString label;
	int64 price = 0;
};

struct Invoice {
	std::vector<LabeledPrice> prices;
	QString currency;

	bool isNameRequested = false;
	bool isPhoneRequested = false;
	bool isEmailRequested = false;
	bool isShippingAddressRequested = false;
	bool isFlexible = false;
	bool isTest = false;

	bool phoneSentToProvider = false;
	bool emailSentToProvider = false;

	[[nodiscard]] bool valid() const {
		return !currency.isEmpty() && !prices.empty();
	}
	[[nodiscard]] explicit operator bool() const {
		return valid();
	}
};

struct ShippingOption {
	QString id;
	QString title;
	std::vector<LabeledPrice> prices;
};

struct ShippingOptions {
	std::vector<ShippingOption> list;
	QString selectedId;
};

struct Address {
	QString address1;
	QString address2;
	QString city;
	QString state;
	QString countryIso2;
	QString postCode;

	[[nodiscard]] bool valid() const {
		return !address1.isEmpty()
			&& !city.isEmpty()
			&& !countryIso2.isEmpty();
	}
	[[nodiscard]] explicit operator bool() const {
		return valid();
	}

	inline bool operator==(const Address &other) const {
		return (address1 == other.address1)
			&& (address2 == other.address2)
			&& (city == other.city)
			&& (state == other.state)
			&& (countryIso2 == other.countryIso2)
			&& (postCode == other.postCode);
	}
	inline bool operator!=(const Address &other) const {
		return !(*this == other);
	}
};

struct RequestedInformation {
	QString name;
	QString phone;
	QString email;
	Address shippingAddress;

	[[nodiscard]] bool empty() const {
		return name.isEmpty()
			&& phone.isEmpty()
			&& email.isEmpty()
			&& !shippingAddress;
	}
	[[nodiscard]] explicit operator bool() const {
		return !empty();
	}

	inline bool operator==(const RequestedInformation &other) const {
		return (name == other.name)
			&& (phone == other.phone)
			&& (email == other.email)
			&& (shippingAddress == other.shippingAddress);
	}
	inline bool operator!=(const RequestedInformation &other) const {
		return !(*this == other);
	}
};

struct SavedCredentials {
	QString id;
	QString title;

	[[nodiscard]] bool valid() const {
		return !id.isEmpty();
	}
	[[nodiscard]] explicit operator bool() const {
		return valid();
	}
};

enum class EditField {
	ShippingInformation,
	Name,
	Email,
	Phone,
};

} // namespace Payments::Ui
