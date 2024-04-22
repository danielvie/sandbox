import { TrashIcon } from "@heroicons/react/24/solid"

interface props_1x {
    label: string;
}

function Input1x(props:props_1x) {
    return (
      <>
        <div className="relative col-span-12">
          <div className="col-span-12">
            <label htmlFor="first-name" className="block text-sm font-medium leading-6 text-gray-900 pl-2">
              {props.label}
            </label>
            <div className="mt-2">
              <input
                placeholder={props.label}
                type="text"
                name="first-name"
                id="first-name"
                autoComplete="given-name"
                className="block w-full h-12 rounded-md border-0 py-1.5 text-gray-900 shadow-sm ring-1 ring-inset ring-gray-300 placeholder:text-gray-400 focus:ring-2 focus:ring-inset focus:ring-indigo-600 sm:text-sm sm:leading-6"
              />
            </div>
          </div>
          <div>
            <TrashIcon className="text-gray-500 h-8 absolute bottom-2 right-2" />
          </div>
        </div>
      </>
    )
}
 
export default Input1x