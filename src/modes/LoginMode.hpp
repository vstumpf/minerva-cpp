#ifndef MINERVA_MODES_LOGINMODE_HPP_
#define MINERVA_MODES_LOGINMODE_HPP_

#include <string>
#include <vector>

#include "modes/Mode.hpp"

#include "render/Renderer.hpp"


class LoginMode : public Mode {
public:
	LoginMode(std::shared_ptr<Renderer> renderer);

	void init() override;
	int run() override;
	void exit() override;

	void update();
};

#endif // MINERVA_MODES_LOGINMODE_HPP_
