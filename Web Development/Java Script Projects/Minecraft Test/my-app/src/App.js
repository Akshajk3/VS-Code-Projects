import { Canvas } from '@react-three/fiber';
import {Sky} from '@react-three/drei';

function App() {
  return (
    <>
      <div>Outside Canvas</div>
      <Canvas>
        <Sky />
      </Canvas>
    </>
  );
}

export default App;
