import { BiListUl, BiSearchAlt2 } from "react-icons/bi";
import { FaChevronRight } from "react-icons/fa";

function FloatMenu(props: { handleOrder: () => void }) {
  return (
    <>
      <div className="fixed bottom-4 right-4">
        <div className="flex gap-4">
          <button className="rounded-full bg-sky-700 p-4 text-2xl text-white shadow-md shadow-gray-400">
            <BiSearchAlt2 />
          </button>
          <button className="rounded-full bg-purple-700 p-4 text-2xl text-white shadow-md shadow-gray-400">
            <BiListUl />
          </button>
          <button
            onClick={props.handleOrder}
            className="rounded-xl bg-gray-200 px-3 py-4 shadow-md shadow-gray-400"
          >
            <div className="flex items-center">
              <FaChevronRight />
              ORDER
            </div>
          </button>
        </div>
      </div>
    </>
  );
}

export default FloatMenu;
